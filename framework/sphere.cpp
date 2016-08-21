#include "sphere.hpp"

Sphere::Sphere():
Shape::Shape(),
middle_{0.0},
radius_{1.0f}
{}

Sphere::Sphere(Material const& mat, std::string const& name, glm::vec3 const& mp, float radius):
Shape::Shape(mat, name),
middle_{mp},
radius_{radius}
{}

Sphere::~Sphere()
{}


//getter{{{
glm::vec3 const& Sphere::get_middle() const
{
	return middle_;
}

float Sphere::get_radius() const
{
	return radius_;
}

// aufgabe5.5
std::ostream& Sphere::print(std::ostream& os) const
{
	Shape::print(os) ;
	os << "middle: <" << middle_.x << "," << middle_.y << "> \n" 
	   << "radius: " << radius_ <<"\n" ;
	return os; 
}
//}}}
// aufgabe5.6

OptiHit Sphere::intersect(Ray const& ray) const
{
  OptiHit hit;
	hit.hit = glm::intersectRaySphere(ray.origin_, ray.direction_,
    middle_, radius_*radius_, hit.distance);
  if (hit.hit)
  {
    hit.closest_shape = this;
    hit.surface_pt = this->calc_surface_pt(ray, hit.distance);
    hit.n = this->calc_n(hit);
    hit.distance = glm::distance(ray.origin_, hit.surface_pt);
  }
	return hit;
}


glm::vec3 Sphere::calc_n(OptiHit const& hit) const
{
  glm::vec3 p = hit.surface_pt;
  return glm::normalize(p - middle_);

}
