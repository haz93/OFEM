#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Display.hpp"
#include <Eigen/Dense>
#include <Eigen/Sparse>


struct Element
{
	void PushStiffnessTriplets(const Eigen::Matrix3f& ElasDMat, std::vector<Eigen::Triplet<float> >& triplets);

	Eigen::Matrix<float, 3, 6> ShpDrvBMat;
	int nodesIds[3];
};

struct Support
{
	enum Type
	{
		UX = 1 << 0,
		UY = 1 << 1,
		UXY = UX | UY
	};
	int node;
	Type type;
};

int							nodesCount;
Eigen::VectorXf				nodesX;
Eigen::VectorXf				nodesY;
Eigen::VectorXf				nodesXdisp;
Eigen::VectorXf				nodesYdisp;
std::vector<int>			elementsids;
Eigen::VectorXf				loads;
std::vector< Element >		elements;
std::vector< Support >	SupportVec;

void Element::PushStiffnessTriplets(const Eigen::Matrix3f& ElasDMat, std::vector<Eigen::Triplet<float> >& triplets)
{
	Eigen::Vector3f x, y;
	x << nodesX[nodesIds[0]], nodesX[nodesIds[1]], nodesX[nodesIds[2]];
	y << nodesY[nodesIds[0]], nodesY[nodesIds[1]], nodesY[nodesIds[2]];

	Eigen::Matrix3f ShapeCoeffCMat;
	ShapeCoeffCMat << Eigen::Vector3f(1.0f, 1.0f, 1.0f), x, y;

	Eigen::Matrix3f IC = ShapeCoeffCMat.inverse();

	for (int i = 0; i < 3; i++)
	{
		ShpDrvBMat(0, 2 * i + 0) = IC(1, i);
		ShpDrvBMat(0, 2 * i + 1) = 0.0f;
		ShpDrvBMat(1, 2 * i + 0) = 0.0f;
		ShpDrvBMat(1, 2 * i + 1) = IC(2, i);
		ShpDrvBMat(2, 2 * i + 0) = IC(2, i);
		ShpDrvBMat(2, 2 * i + 1) = IC(1, i);
	}
	
	Eigen::Matrix<float, 6, 6> K = ShpDrvBMat.transpose() * ElasDMat * ShpDrvBMat * ShapeCoeffCMat.determinant() / 2.0f;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Eigen::Triplet<float> trplt11(2 * nodesIds[i] + 0, 2 * nodesIds[j] + 0, K(2 * i + 0, 2 * j + 0));
			Eigen::Triplet<float> trplt12(2 * nodesIds[i] + 0, 2 * nodesIds[j] + 1, K(2 * i + 0, 2 * j + 1));
			Eigen::Triplet<float> trplt21(2 * nodesIds[i] + 1, 2 * nodesIds[j] + 0, K(2 * i + 1, 2 * j + 0));
			Eigen::Triplet<float> trplt22(2 * nodesIds[i] + 1, 2 * nodesIds[j] + 1, K(2 * i + 1, 2 * j + 1));

			triplets.push_back(trplt11);
			triplets.push_back(trplt12);
			triplets.push_back(trplt21);
			triplets.push_back(trplt22);
		}
	}
}

void SetSupports(Eigen::SparseMatrix<float>::InnerIterator& it, int index)
{
	if (it.row() == index || it.col() == index)
	{
		it.valueRef() = it.row() == it.col() ? 1.0f : 0.0f;
	}
}

void ApplySupports(Eigen::SparseMatrix<float>& K, const std::vector<Support>& SupportVec)
{
	std::vector<int> SupportOffsets;

	for (std::vector<Support>::const_iterator it = SupportVec.begin(); it != SupportVec.end(); ++it)
	{
		if (it->type & Support::UX)
		{
			SupportOffsets.push_back(2 * it->node + 0);
		}
		if (it->type & Support::UY)
		{
			SupportOffsets.push_back(2 * it->node + 1);
		}
	}

	for (int k = 0; k < K.outerSize(); ++k)
	{
		for (Eigen::SparseMatrix<float>::InnerIterator it(K, k); it; ++it)
		{
			for (std::vector<int>::iterator itd = SupportOffsets.begin(); itd != SupportOffsets.end(); ++itd)
			{
				SetSupports(it, *itd);
			}
		}
	}
}


int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "usage: " << argv[0] << " <input file> <output file>\n";
		return 1;
	}

	std::ifstream infile(argv[1]);
	std::ofstream outfile(argv[2]);

	float poissonRatio, youngModulus;
	infile >> poissonRatio >> youngModulus;

	Eigen::Matrix3f ElasDMat;
	ElasDMat <<
		1.0f, poissonRatio, 0.0f,
		poissonRatio, 1.0, 0.0f,
		0.0f, 0.0f, (1.0f - poissonRatio) / 2.0f;

	ElasDMat *= youngModulus / (1.0f - pow(poissonRatio, 2.0f));

	infile >> nodesCount;
	nodesX.resize(nodesCount);
	nodesY.resize(nodesCount);
	nodesXdisp.resize(nodesCount);
	nodesYdisp.resize(nodesCount);

	for (int i = 0; i < nodesCount; ++i)
	{
		infile >> nodesX[i] >> nodesY[i];
	}

	int elementCount;
	infile >> elementCount;

	for (int i = 0; i < elementCount; ++i)
	{
		Element element;

		infile >> element.nodesIds[0] >> element.nodesIds[1] >> element.nodesIds[2];
		elementsids.push_back(element.nodesIds[0]);
		elementsids.push_back(element.nodesIds[1]);
		elementsids.push_back(element.nodesIds[2]);
		elements.push_back(element);
	}
	int SupportCount;
	infile >> SupportCount;

	for (int i = 0; i < SupportCount; ++i)
	{
		Support supp;
		int type;
		infile >> supp.node >> type;
		supp.type = static_cast<Support::Type>(type);
		SupportVec.push_back(supp);
	}

	loads.resize(2 * nodesCount);
	loads.setZero();
	int loadsCount;
	infile >> loadsCount;


	for (int i = 0; i < loadsCount; ++i)
	{
		int node;
		float x, y;
		infile >> node >> x >> y;
		loads[2 * node + 0] = x;
		loads[2 * node + 1] = y;
	}

	std::vector<Eigen::Triplet<float> > triplets;
	for (std::vector<Element>::iterator it = elements.begin(); it != elements.end(); ++it)
	{
		it->PushStiffnessTriplets(ElasDMat, triplets);
	}

	Eigen::SparseMatrix<float> StiffnessKMat(2 * nodesCount, 2 * nodesCount);
	StiffnessKMat.setFromTriplets(triplets.begin(), triplets.end());

	ApplySupports(StiffnessKMat, SupportVec);

	Eigen::SimplicialLDLT<Eigen::SparseMatrix<float> > solver(StiffnessKMat);

	Eigen::VectorXf DispVec = solver.solve(loads);
	int dispcounter = 0;
	for (int i = 0; i < nodesCount; ++i)
	{
		nodesXdisp[i] = nodesX[i] + DispVec[dispcounter];
		//test = nodesXdisp[i];
		//std::cout << test << std::endl;

		nodesYdisp[i] = nodesY[i] + DispVec[dispcounter+1];
		//test2 = nodesYdisp[i];
		//std::cout << test2 << std::endl;

		dispcounter += 2;

	}
	
	dsp::dispxx n;
	//outfile << DispVec << std::endl;

	std::vector<float> PostPVec;

			for (std::vector<Element>::iterator it = elements.begin(); it != elements.end(); ++it)
	{
			Eigen::Matrix<float, 6, 1> delta;
			delta << DispVec.segment<2>(2 * it->nodesIds[0]),
				DispVec.segment<2>(2 * it->nodesIds[1]),
			DispVec.segment<2>(2 * it->nodesIds[2]);

		Eigen::Vector3f sigma = ElasDMat * it->ShpDrvBMat * delta;
		//float sigma_mises = sqrt(sigma[0] * sigma[0] - sigma[0] * sigma[1] + sigma[1] * sigma[1] + 3.0f * sigma[2] * sigma[2]);
		float sigma_mises = sigma[0];
		PostPVec.push_back(sigma_mises);

	//	outfile << sigma_mises << std::endl;
	}

	n.maindisplay(&nodesX, &nodesY, nodesCount, elementCount, &nodesXdisp, &nodesYdisp, &elementsids, PostPVec);




		return 0;
	}

