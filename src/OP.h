#ifndef TSP_H
#define TSP_H
#include "BranchBound.h"

class OP{


public:
	//constructor
	OP();
	//destructor
	~OP();

	//get the current location of robot
	void GetCurrentLocation(const pcl::PointCloud<pcl::PointXYZ>::Ptr & pCloud,
		                    const std::vector<std::vector<int>> & vGridPointIdx,
		                    const int & iRobot);

	bool IsWideGrid(const std::vector<CofidenceValue> & vReWardMap,
		                                     const int & iQueryIdx);

	//get the newly generated nodes
	void GetNewNode(const std::vector<CofidenceValue> & vReWardMap,
		            const pcl::PointCloud<pcl::PointXYZ>::Ptr & pCloud,
	             	const std::vector<std::vector<int>> & vGridPointIdx,
	            	const int & vNewNodeIdxs,
					float fSuppressionR = 5.0);

	//get the newly generated nodes
	void GetNewNodes(const std::vector<CofidenceValue> & vReWardMap,
		             const pcl::PointCloud<pcl::PointXYZ>::Ptr & pCloud,
		             const std::vector<std::vector<int>> & vGridPointIdx,
		             const std::vector<int> & vNewNodeIdxs,
					 float fSuppressionR = 5.0);

	bool RefreshNodes(std::vector<CofidenceValue> & vReWardMap, 
		                            float fMinThreshold = 0.8);

	//get the current node index
	void GetCurNodesIdx(int f_iRbtPstion);

	//compute the center of point clouds within a query grid
	static pcl::PointXYZ ComputeCentersPosition(const pcl::PointCloud<pcl::PointXYZ>::Ptr & pCloud,
		                                 const std::vector<std::vector<int>> & vGridPointIdx,
	                                     const int & iQueryIdx);

	static bool OP::ComputeCentersPosition(pcl::PointXYZ & oCenter,
		const pcl::PointCloud<pcl::PointXYZ>::Ptr & pCloud,
		const std::vector<std::vector<int>> & vGridPointIdx,
		const int & iQueryIdx);

	//compute the Euclidean distance
	float ComputeEuclideanDis(const pcl::PointXYZ & oQueryPoint,
		                      const pcl::PointXYZ & oTargetPoint);


	//the cost function of a pairs of nodes
	float CostFunction(const std::vector<CofidenceValue> & vReWardMap,
		                    const int & vQueryIdx,
		                    const pcl::PointXYZ & oQueryCenter,
		                    const int & vTargetIdx,
		                    const pcl::PointXYZ & oTargetCenter);

	float ObjectiveFunction(const std::vector<CofidenceValue> & vReWardMap,
		                                             const int & vQueryIdx,
		                                const pcl::PointXYZ & oQueryCenter,
		                                            const int & vTargetIdx,
		                               const pcl::PointXYZ & oTargetCenter);

	//GTR methods which proposed in  
	bool GTR(const std::vector<CofidenceValue> & vReWardMap);

	//branch and bound method to solve op
	bool BranchBoundMethod(const std::vector<CofidenceValue> & vReWardMap);

	//Outout the history of traveling nodes
	void OutputVisitedNodes(std::vector<int> & vOutputNodes);
	int OutputVisitedNodes(std::vector<pcl::PointXYZ> & vOutputNodes,
		                    const pcl::PointCloud<pcl::PointXYZ>::Ptr & pCloud,
		                    const std::vector<std::vector<int>> & vGridPointIdx);

    void OutputUnVisitedNodes(std::vector<int> & vOutputNodes);
	void OutputUnVisitedNodes(std::vector<pcl::PointXYZ> & vOutputNodes);

	//unvisited nodes or nodes to be visited
	std::vector<int> m_vUnVisitNodeIdx;
	std::vector<bool> m_vUnVisitIsWide;

    //the corresponding center position of unvisited nodes
	std::vector<pcl::PointXYZ> m_vUnVisitCenters;

	//OP node which has been visited
	std::vector<int> m_vVisitedNodeIdx;
	//std::vector<pcl::PointXYZ> vVisitedCenters;

private:

	//the grid index where the current robot is  
	int m_iCurrentNodeIdx;
	pcl::PointXYZ m_oCurrentCenter;

	//
	BranchBound BBSolver;

	float m_fWideThr;

};



#endif
