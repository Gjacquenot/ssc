/*
 * KinematicsTests.cpp
 *
 *  Created on: 1 avr. 2014
 *      Author: maroff
 */

#include "KinematicsTests.hpp"
#include "test_macros.hpp"
#include "Kinematics.hpp"
#include "FrameException.hpp"
#include "rotation_matrix_builders.hpp"
#include "EulerAngles.hpp"
#include "Point.hpp"

#include <cmath>

KinematicsTests::KinematicsTests() : a(DataGenerator(122))
{
}

KinematicsTests::~KinematicsTests()
{
}

void KinematicsTests::SetUp()
{
}

void KinematicsTests::TearDown()
{
}

#define PI (4.*atan(1.))

void KinematicsTests::add_frame(Kinematics& k, const std::string& name, const double x, const double y, const double z, const double phi, const double theta, const double psi) const
{
    using namespace kinematics;
    const RotationMatrix R = rotation_matrix<INTRINSIC, ORDERED_BY_ANGLE, CARDAN, 3, 2, 1>(EulerAngles(phi,theta,psi));
    const Point P("fixed", x, y, z);
    k.add_frame(name, P, R);
}


TEST_F(KinematicsTests, the_reference_frame_should_be_correct_when_changing_reference_frame)
{
    Kinematics k;
    const Point P("fixed", 1, 2, 3);
    for (size_t i = 0 ; i < 40 ; ++i)
    {
        const std::string name = a.random<std::string>();
        add_frame(k, name, 1, 2, 3, PI/3, PI/4, PI/6);
        const Point Q("fixed", 4, 0, 1);
        const Point R = k.project(Q, name);
        ASSERT_EQ(name, R.frame);
    }
}

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
typedef float Weight;
typedef boost::property<boost::edge_weight_t, Weight> WeightProperty;
typedef boost::property<boost::vertex_name_t, std::string> NameProperty;

typedef boost::adjacency_list < boost::listS, boost::vecS, boost::undirectedS,
NameProperty, WeightProperty > Graph;

typedef boost::graph_traits < Graph >::vertex_descriptor Vertex;

typedef boost::property_map < Graph, boost::vertex_index_t >::type IndexMap;
typedef boost::property_map < Graph, boost::vertex_name_t >::type NameMap;

typedef boost::iterator_property_map < Vertex*, IndexMap, Vertex, Vertex& > PredecessorMap;
typedef boost::iterator_property_map < Weight*, IndexMap, Weight, Weight& > DistanceMap;
typedef std::vector<Graph::edge_descriptor> PathType;
TEST_F(KinematicsTests, reimplementation_of_robwork)
{
    Graph g;

    Vertex A = boost::add_vertex(std::string("A"), g);
    Vertex B = boost::add_vertex(std::string("B"), g);
    Vertex C = boost::add_vertex(std::string("C"), g);
    Vertex D = boost::add_vertex(std::string("D"), g);
    Vertex E = boost::add_vertex(std::string("E"), g);
    Vertex F = boost::add_vertex(std::string("F"), g);
    Vertex G = boost::add_vertex(std::string("G"), g);
    Vertex H = boost::add_vertex(std::string("H"), g);
    Vertex I = boost::add_vertex(std::string("I"), g);


    boost::add_edge (A, B, 1, g);
    boost::add_edge (A, C, 1, g);
    boost::add_edge (B, D, 1, g);
    boost::add_edge (C, E, 1, g);
    boost::add_edge (C, F, 1, g);
    boost::add_edge (D, G, 1, g);
    boost::add_edge (D, H, 1, g);
    boost::add_edge (D, I, 1, g);

    std::vector<Vertex> predecessors(boost::num_vertices(g)); // To store parents
    std::vector<Weight> distances(boost::num_vertices(g)); // To store distances

    IndexMap indexMap = boost::get(boost::vertex_index, g);
    PredecessorMap predecessorMap(&predecessors[0], indexMap);
    DistanceMap distanceMap(&distances[0], indexMap);

    // Compute shortest paths from v0 to all vertices, and store the output in predecessors and distances
    // boost::dijkstra_shortest_paths(g, v0, boost::predecessor_map(predecessorMap).distance_map(distanceMap));
    // This is exactly the same as the above line - it is the idea of "named parameters" - you can pass the
    // prdecessor map and the distance map in any order.
    boost::dijkstra_shortest_paths(g, C, boost::distance_map(distanceMap).predecessor_map(predecessorMap));

    PathType path;
    NameMap nameMap = boost::get(boost::vertex_name, g);
    Vertex v = D; // We want to start at the destination and work our way back to the source
    for(Vertex u = predecessorMap[v]; // Start by setting 'u' to the destintaion node's predecessor
      u != v; // Keep tracking the path until we get to the source
      v = u, u = predecessorMap[v]) // Set the current vertex to the current predecessor, and the predecessor to one level up
    {
    std::pair<Graph::edge_descriptor, bool> edgePair = boost::edge(u, v, g);
    Graph::edge_descriptor edge = edgePair.first;

    path.push_back( edge );
    }

    std::cout << "Shortest path from v0 to v3:" << std::endl;
    for(PathType::reverse_iterator pathIterator = path.rbegin(); pathIterator != path.rend(); ++pathIterator)
    {
    std::cout << nameMap[boost::source(*pathIterator, g)] << " -> " << nameMap[boost::target(*pathIterator, g)]
              << " = " << boost::get( boost::edge_weight, g, *pathIterator ) << std::endl;

    }

}

TEST_F(KinematicsTests, can_change_the_reference_frame_of_a_point)
{
    Kinematics k;
    add_frame(k, "b", 1, 2, 3, PI/3, PI/4, PI/6);
    const Point Q("fixed", 4, 0, 1);
    const Point R = k.project(Q, "b");
    ASSERT_DOUBLE_EQ(3*sqrt(6)/4-sqrt(2)/2+sqrt(2), R.x);
}
/*
TEST_F(KinematicsTests, should_be_able_to_change_the_position_of_a_reference_frame)
{
    Kinematics k;
    add_frame(k, "b", 0, 0, 0, PI/3, PI/4, PI/6);
    const Point P("fixed", 4, 0, 1);
    const Point Q("fixed", 1, 2, 3);
    k.update_position("b", Q);
    const Point R = k.project(P, "b");
    ASSERT_DOUBLE_EQ(3*sqrt(6)/4-sqrt(2)/2+sqrt(2), R.x);
}


TEST_F(KinematicsTests, cannot_create_point_in_non_existent_frame)
{
    Kinematics k;
    const std::string name = a.random<std::string>();
    ASSERT_THROW(k.make_point(name, a.random<double>(), a.random<double>(), a.random<double>()), KinematicsException);
}

TEST_F(KinematicsTests, cannot_define_the_same_reference_frame_more_than_once)
{
    Kinematics k;
    const std::string name = a.random<std::string>();
    add_frame(k, name, 1, 2, 3, 4, 5, 6);
    ASSERT_NO_THROW(k.add_frame(name, P, ang));
    ASSERT_THROW(add_frame(k, name, 1, 2, 3, 4, 5, 6), KinematicsException);
}

TEST_F(KinematicsTests, cannot_project_a_point_in_a_non_existent_frame)
{
    Kinematics k;
    const auto P = k.make_point("fixed", 1, 2, 3);
    ASSERT_THROW(k.project(P, a.random<std::string>()), KinematicsException);
}

TEST_F(KinematicsTests, can_project_a_velocity_screw_in_a_different_frame)
{
    Kinematics k;
    add_frame(k, "b", 1,2,47,0,23,4);
    const VelocityScrew v("b", -1,-2,7,8,9,16);

}

TEST_F(KinematicsTests, can_project_a_wrench_in_a_different_frame)
{

}

TEST_F(KinematicsTests, cannot_project_a_velocity_screw_in_a_non_existent_frame)
{

}

TEST_F(KinematicsTests, cannot_project_a_wrench_in_a_non_existent_frame)
{

}

kinematics::FramePtr KinematicsTests::get_random_frame(const std::string& name)
{
    const kinematics::Vector3DInFrame u(base, a.random<double>(),
                                              a.random<double>(),
                                              a.random<double>());
    return kinematics::Frame::make_new(u,name);
}

TEST_F(KinematicsTests, example)
{
//! [KinematicsTests example]
    const kinematics::Vector3DInFrame P(base, 1, 2, 3);
    rw::math::Rotation3D<double> R;

    const auto F1 = kinematics::Frame::make_new(P, R, a.random<std::string>());
    kinematics::Velocity v(P,F1,base);

//! [KinematicsTests example]
//! [KinematicsTests expected output]
//! [KinematicsTests expected output]
}

TEST_F(KinematicsTests, cannot_have_two_frames_with_same_name)
{
    const std::string frame_name = a.random<std::string>();
    ASSERT_NO_THROW(get_random_frame(frame_name));
    ASSERT_THROW(get_random_frame(frame_name), FrameException);
    ASSERT_NO_THROW(get_random_frame(a.random<std::string>()));
}

TEST_F(KinematicsTests, all_frames_must_have_a_name)
{
    ASSERT_THROW(get_random_frame(""), FrameException);
}

TEST_F(KinematicsTests, base_is_not_a_valid_frame_name)
{
    ASSERT_THROW(get_random_frame("base"), FrameException);
}


TEST_F(KinematicsTests, can_get_coordinates_of_a_point_in_another_reference_frame_simply_translated)
{
    //! [KinematicsTests operator/]
    const kinematics::Vector3DInFrame u1(base, 1,//a.random<double>(),
                                               2,//        a.random<double>(),
                                               3);//        a.random<double>());
    const kinematics::Vector3DInFrame u2(base, 2,//a.random<double>(),
                                               5,//        a.random<double>(),
                                               9);//        a.random<double>());
    const auto F1 = kinematics::Frame::make_new(u1, "F1");//a.random<std::string>());
    const auto F2 = kinematics::Frame::make_new(u2, "F2");// a.random<std::string>());
    const kinematics::Vector3DInFrame P(F1, 1,//a.random<double>(),
                                            1,//        a.random<double>(),
                                            1);//        a.random<double>());

    const auto P_projected_in_F2 = P / F2;
    //! [KinematicsTests operator/]

    ASSERT_DOUBLE_EQ(u1[0]-u2[0]+P[0], P_projected_in_F2[0]);
    ASSERT_DOUBLE_EQ(u1[1]-u2[1]+P[1], P_projected_in_F2[1]);
    ASSERT_DOUBLE_EQ(u1[2]-u2[2]+P[2], P_projected_in_F2[2]);
}

TEST_F(KinematicsTests, DISABLED_can_get_coordinates_of_a_point_in_another_reference_frame_simply_rotated)
{
    ASSERT_TRUE(false);
}

TEST_F(KinematicsTests, DISABLED_can_get_coordinates_of_a_point_in_another_reference_frame_translated_and_rotated)
{
    ASSERT_TRUE(false);
}

TEST_F(KinematicsTests, DISABLED_should_be_able_to_perform_round_trip_transform_on_point_by_applying_inverse_transform)
{
    ASSERT_TRUE(false);
}
*/