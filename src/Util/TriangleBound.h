#ifndef TRAINGLE_BOUND_H
#define TRIANGLE_BOUND_H

#include "Bound.h"
#include "BoxBound.h"
#include <vector>

/**
 * @brief Class for bounds for spikes
 * 
 * Provides collision detection between a boxBound and TriangleBound
 * 
 */
class TriangleBound: public Bound{
private:
	sf::Vector2f m_base_pt_1;/**<Co-ordinates of base corner wrt the top left corner of the 42x42 tile it is in*/
	sf::Vector2f m_base_pt_2;/**<Co-ordinates of base corner wrt the top left corner of the 42x42 tile it is in*/
	sf::Vector2f m_tip_pt;/**<Co-ordinates of tip of the spike wrt the top left corner of the 42x42 tile it is in*/

	float m_base;
	float m_height;
	float m_enclosingRadius;
	sf::Vector2f m_center;

	static bool checkBroadPhaseCollision(const BoxBound& playerBound, const TriangleBound& spike);
	static bool checkNarrowPhaseCollision(const BoxBound& playerBound, const TriangleBound& spike);

public:
	TriangleBound();
	TriangleBound(sf::Vector2f position, sf::Vector2f base_pt_1
		, sf::Vector2f base_pt_2, sf::Vector2f tip_pt, BOUNDNAME name = BOUNDNAME::SPIKE);

	virtual const float getWidth() const override;
	virtual const float getHeight() const override;
	const sf::Vector2f getCenter() const;
	const float getEnclosingRadius() const;
	const std::vector<sf::Vector2f> getCorners() const;

	static bool checkCollision(const BoxBound& playerBound, const TriangleBound& spike);
};

#endif