/// \file DQMDQMCartesianVector.cc
/*
 *
 * DQMDQMCartesianVector.cc source template automatically generated by a class generator
 * Creation date : ven. avr. 8 2016
 * 
 * @author J. Marshall (from PandoraSDK)
 * @copyright 
 */


#include "dqm4hep/CartesianVector.h"

namespace dqm4hep {

  namespace core {

    float CartesianVector::getCosOpeningAngle(const CartesianVector &rhs) const
    {
      const float magnitudesSquared(this->getMagnitudeSquared() * rhs.getMagnitudeSquared());

      if (magnitudesSquared < std::numeric_limits<float>::epsilon())
        throw StatusCodeException(STATUS_CODE_NOT_INITIALIZED);

      float cosTheta = this->getDotProduct(rhs) / sqrt(magnitudesSquared);

      if (cosTheta > 1.f)
      {
        cosTheta = 1.f;
      }
      else if (cosTheta < -1.f)
      {
        cosTheta = -1.f;
      }

      return cosTheta;
    }

    //------------------------------------------------------------------------------------------------------------------------------------------

    void CartesianVector::getSphericalCoordinates(float &radius, float &phi, float &theta) const
    {
      const float magnitude(this->getMagnitude());

      if (fabs(magnitude) < std::numeric_limits<float>::epsilon())
        throw StatusCodeException(STATUS_CODE_INVALID_PARAMETER);

      radius = magnitude;
      phi    = atan2(m_y, m_x);
      theta  = acos(m_z / radius);
    }

    //------------------------------------------------------------------------------------------------------------------------------------------

    void CartesianVector::getCylindricalCoordinates(float &radius, float &phi, float &z) const
    {
      const float magnitude(this->getMagnitude());

      if (fabs(magnitude) < std::numeric_limits<float>::epsilon())
        throw StatusCodeException(STATUS_CODE_INVALID_PARAMETER);

      radius = sqrt(m_y * m_y + m_x * m_x);
      phi    = atan2(m_y, m_x);
      z      = m_z;
    }

    //------------------------------------------------------------------------------------------------------------------------------------------

    CartesianVector CartesianVector::getUnitVector() const
    {
      const float magnitude(this->getMagnitude());

      if (fabs(magnitude) < std::numeric_limits<float>::epsilon())
        throw StatusCodeException(STATUS_CODE_INVALID_PARAMETER);

      return CartesianVector(m_x / magnitude, m_y / magnitude, m_z / magnitude);
    }

    //------------------------------------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------------------------------

    std::ostream &operator<<(std::ostream & stream, const CartesianVector& cartesianVector)
    {
      stream  << "  x: " << cartesianVector.getX()
                << "  y: " << cartesianVector.getY()
                << "  z: " << cartesianVector.getZ()
                << " length: " << cartesianVector.getMagnitude();

      return stream;
    }

  }

}

