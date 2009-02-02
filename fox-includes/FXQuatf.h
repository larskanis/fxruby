/********************************************************************************
*                                                                               *
*              S i n g l e - P r e c i s i o n  Q u a t e r n i o n             *
*                                                                               *
*********************************************************************************
* Copyright (C) 1994,2006 by Jeroen van der Zijp.   All Rights Reserved.        *
*********************************************************************************
* This library is free software; you can redistribute it and/or                 *
* modify it under the terms of the GNU Lesser General Public                    *
* License as published by the Free Software Foundation; either                  *
* version 2.1 of the License, or (at your option) any later version.            *
*                                                                               *
* This library is distributed in the hope that it will be useful,               *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU             *
* Lesser General Public License for more details.                               *
*                                                                               *
* You should have received a copy of the GNU Lesser General Public              *
* License along with this library; if not, write to the Free Software           *
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.    *
*********************************************************************************
* $Id: FXQuatf.h 2344 2006-02-12 21:19:36Z lyle $                           *
********************************************************************************/
#ifndef FXQUATF_H
#define FXQUATF_H


namespace FX {


class FXMat3f;


/// Single-precision quaternion
class FXAPI FXQuatf : public FXVec4f {
public:

  /// Construct
  FXQuatf(){}

  /// Copy constructor
  FXQuatf(const FXQuatf& q):FXVec4f(q){}

  /// Construct from components
  FXQuatf(FXfloat xx,FXfloat yy,FXfloat zz,FXfloat ww):FXVec4f(xx,yy,zz,ww){}

  /// Construct from array of floats
  FXQuatf(const FXfloat v[]):FXVec4f(v){}

  /// Construct from axis and angle
  FXQuatf(const FXVec3f& axis,FXfloat phi=0.0f);

  /// Construct from euler angles yaw (z), pitch (y), and roll (x)
  FXQuatf(FXfloat roll,FXfloat pitch,FXfloat yaw);

  /// Construct quaternion from two unit vectors
  FXQuatf(const FXVec3f& fr,const FXVec3f& to);

  /// Construct quaternion from three axes
  FXQuatf(const FXVec3f& ex,const FXVec3f& ey,const FXVec3f& ez);

  /// Construct quaternion from 3x3 matrix
  FXQuatf(const FXMat3f& mat);

  /// Adjust quaternion length
  FXQuatf& adjust();

  /// Set quaternion from axis and angle
  void setAxisAngle(const FXVec3f& axis,FXfloat phi=0.0f);

  /// Obtain axis and angle from quaternion
  void getAxisAngle(FXVec3f& axis,FXfloat& phi) const;

  /// Set quaternion from roll (x), pitch (y), yaw (z)
  void setRollPitchYaw(FXfloat roll,FXfloat pitch,FXfloat yaw);
  void getRollPitchYaw(FXfloat& roll,FXfloat& pitch,FXfloat& yaw) const;

  /// Set quaternion from yaw (z), pitch (y), roll (x)
  void setYawPitchRoll(FXfloat yaw,FXfloat pitch,FXfloat roll);
  void getYawPitchRoll(FXfloat& yaw,FXfloat& pitch,FXfloat& roll) const;

  /// Set quaternion from roll (x), yaw (z), pitch (y)
  void setRollYawPitch(FXfloat roll,FXfloat yaw,FXfloat pitch);
  void getRollYawPitch(FXfloat& roll,FXfloat& yaw,FXfloat& pitch) const;

  /// Set quaternion from pitch (y), roll (x),yaw (z)
  void setPitchRollYaw(FXfloat pitch,FXfloat roll,FXfloat yaw);
  void getPitchRollYaw(FXfloat& pitch,FXfloat& roll,FXfloat& yaw) const;

  /// Set quaternion from pitch (y), yaw (z), roll (x)
  void setPitchYawRoll(FXfloat pitch,FXfloat yaw,FXfloat roll);
  void getPitchYawRoll(FXfloat& pitch,FXfloat& yaw,FXfloat& roll) const;

  /// Set quaternion from yaw (z), roll (x), pitch (y)
  void setYawRollPitch(FXfloat yaw,FXfloat roll,FXfloat pitch);
  void getYawRollPitch(FXfloat& yaw,FXfloat& roll,FXfloat& pitch) const;

  /// Set quaternion from axes
  void setAxes(const FXVec3f& ex,const FXVec3f& ey,const FXVec3f& ez);

  /// Get quaternion axes
  void getAxes(FXVec3f& ex,FXVec3f& ey,FXVec3f& ez) const;

  /// Obtain local x axis
  FXVec3f getXAxis() const;

  /// Obtain local y axis
  FXVec3f getYAxis() const;

  /// Obtain local z axis
  FXVec3f getZAxis() const;

  /// Exponentiate quaternion
  FXQuatf exp() const;

  /// Take logarithm of quaternion
  FXQuatf log() const;

  /// Invert quaternion
  FXQuatf invert() const;

  /// Invert unit quaternion
  FXQuatf unitinvert() const;

  /// Conjugate quaternion
  FXQuatf conj() const;

  /// Construct quaternion from arc a->b on unit sphere
  FXQuatf& arc(const FXVec3f& a,const FXVec3f& b);

  /// Spherical lerp
  FXQuatf& lerp(const FXQuatf& u,const FXQuatf& v,FXfloat f);

  /// Multiply quaternions
  FXQuatf operator*(const FXQuatf& q) const;

  /// Rotation of a vector by a quaternion
  FXVec3f operator*(const FXVec3f& v) const;
  };


}

#endif
