#include "TriangleBound.h"
#include <iostream>
#include <cmath>

/**
 * @brief Returns square of distance between 2 points
 * 
 * @param p1 Co-ordinates of first point
 * @param p2 Co-ordinates of second point
 * @return float Distance
 */
float distance_sqr(sf::Vector2f p1, sf::Vector2f p2){
	return (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y);
}

/**
 * @brief Returns distance between point p and line formed by points p1, p2
 * 
 * @param p 
 * @param p1 
 * @param p2 
 * @return float 
 */
float distance_to_line(sf::Vector2f p, sf::Vector2f p1, sf::Vector2f p2){
	// Coefficients of line joining p1 and p2;
	float A = p1.y - p2.y;
	float B = p2.x - p1.x;
	float C = p1.x*p2.y - p2.x*p1.y;

	return fabs(A*p.x + B*p.y + C) / sqrt(A*A + B*B);
}

/**
 * @brief Construct a new Triangle Bound::Triangle Bound object
 * 
 */
TriangleBound::TriangleBound():
	Bound(BOUNDTYPE::TRIANGLE, BOUNDNAME::SPIKE)
{
}

/**
 * @brief Construct a new Triangle Bound::Triangle Bound object
 * 
 * @param position Position of the top left corner of the 42x42 tile it is part of
 * @param base_pt_1 Co-ordinates relative to "position"
 * @param base_pt_2 Co-ordinates relative to "position"
 * @param tip_pt Co-ordinates relative to "position"
 * @param name Name of the TriangleBound
 */
TriangleBound::TriangleBound(sf::Vector2f position, sf::Vector2f base_pt_1
	, sf::Vector2f base_pt_2, sf::Vector2f tip_pt, BOUNDNAME name):
	Bound(BOUNDTYPE::TRIANGLE, name),
	m_base_pt_1(base_pt_1),
	m_base_pt_2(base_pt_2),
	m_tip_pt(tip_pt),
	m_base(sqrt(distance_sqr(m_base_pt_1, m_base_pt_2))),
	m_height(distance_to_line(m_tip_pt, m_base_pt_1, m_base_pt_2)),
	m_enclosingRadius(std::max(m_base/2.f, m_height))
{
	sf::Transformable::setPosition(position);
	m_center = (m_base_pt_1 + m_base_pt_2)/2.f + sf::Transformable::getPosition();
}

/**
 * @brief Returns the length of the base
 * 
 * @return const float 
 */
const float TriangleBound::getWidth() const {
	return m_base;
}

/**
 * @brief Returns the height of the triangle
 * 
 * @return const float 
 */
const float TriangleBound::getHeight() const {
	return m_height;
}

/**
 * @brief Returns the absolute position of the center of the enclosing center
 * 
 * @return const sf::Vector2f 
 */
const sf::Vector2f TriangleBound::getCenter() const {
	return m_center;
}

/**
 * @brief Get radius of circle enclosing the whole triangle
 * 
 * @return const float
 */
const float TriangleBound::getEnclosingRadius() const {
	return m_enclosingRadius;
}

/**
 * @brief Return the positions of the corners relative to this->getPosition()
 * 
 * @return const std::vector<sf::Vector2f> 
 */
const std::vector<sf::Vector2f> TriangleBound::getCorners() const {
	return {m_base_pt_1, m_base_pt_2, m_tip_pt};
}

/**
 * @brief Check collision between a boxbound(the player) and a triangle bounds
 * 
 * First does a "broad phase collision detection", and if it is triggered, then does a 
 * "narrow phase collision detection". This is done as the narrow phase is resource intensive
 * while broad phase detection is very fast.
 * 
 * @param playerBound 
 * @param spike 
 * @return true 
 * @return false 
 */
bool TriangleBound::checkCollision(const BoxBound& playerBound, const TriangleBound& spike){
	if(checkBroadPhaseCollision(playerBound, spike)){
		// std::cout << "BroadPhase Collision!!" << std::endl;
		return checkNarrowPhaseCollision(playerBound, spike);
	}
	return false;
}

bool TriangleBound::checkBroadPhaseCollision(const BoxBound& playerBound
	, const TriangleBound& spike)
{
	return distance_sqr(playerBound.getCenter(), spike.getCenter()) 
		< (playerBound.getEnclosingRadius() + spike.getEnclosingRadius()) 
			* (playerBound.getEnclosingRadius() + spike.getEnclosingRadius());
}

std::vector<sf::Vector2f> generate_pts_in_between(sf::Vector2f p1, sf::Vector2f p2, int count);

bool TriangleBound::checkNarrowPhaseCollision(const BoxBound& playerBound
	, const TriangleBound& spike)
{
	sf::FloatRect playerRect(playerBound.getPosition(), sf::Vector2f(playerBound.getWidth()
		, playerBound.getHeight()));

	auto corners = spike.getCorners();//Positions relative to top left
	for(auto& corner: corners){
		corner += spike.getPosition();// Abs position
	}
	auto num_of_corners = corners.size();
	int num_of_inbtw_pts = 7;

	for(long unsigned i = 0; i < num_of_corners; ++i){
		auto pts = generate_pts_in_between(corners[i], corners[(i+1) % num_of_corners]
			, num_of_inbtw_pts);
		for(auto pt: pts){
			if(playerRect.contains(pt)){
				// std::cout << "NarrowPhase Collision!!" << std::endl;
				return true;
			}
		}
	}

	return false;
}

std::vector<sf::Vector2f> generate_pts_in_between(sf::Vector2f p1, sf::Vector2f p2, int count){
	std::vector<sf::Vector2f> pts;

	pts.push_back(p1);
	for(int i = 1; i <= count - 2; ++i){
		// Section formula (ratio is i : (count - i))
		sf::Vector2f pt = (static_cast<float>(i)*p2 + static_cast<float>(count-i)*p1)
			/ static_cast<float>(count);
		pts.push_back(pt);
	}
	pts.push_back(p2);

	return pts;
}