/********************************************************************************
*                                                                               *
*              D o u b l e - P r e c i s i o n  Q u a t e r n i o n             *
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
* $Id: FXQuatd.h 2344 2006-02-12 21:19:36Z lyle $                           *
********************************************************************************/
#ifndef FXQUATD_H
#define FXQUATD_H


namespace FX {


class FXMat3d;


/// Double-precision quaternion
class FXAPI FXQuatd : public FXVec4d {
public:

  /// Constructors
  FXQuatd(){}

  /// Copy constructor
  FXQuatd(const FXQuatd& q):FXVec4d(q){}

  /// Construct from components
  FXQuatd(FXdouble xx,FXdouble yy,FXdouble zz,FXdouble ww):FXVec4d(xx,yy,zz,ww){}

  /// Construct from array of doubles
  FXQuatd(const FXdouble v[]):FXVec4d(v){}

  /// Construct from axis and angle
  FXQuatd(const FXVec3d& axis,FXdouble phi=0.0);

  /// Construct from euler angles yaw (z), pitch (y), and roll (x)
  FXQuatd(FXdouble roll,FXdouble pitch,FXdouble yaw);

  /// Construct quaternion from two unit vectors
  FXQuatd(const FXVec3d& fr,const FXVec3d& to);

  /// Construct quaternion from three axes
  FXQuatd(const FXVec3d& ex,const FXVec3d& ey,const FXVec3d& ez);

  /// Construct quaternion from 3x3 matrix
  FXQuatd(const FXMat3d& mat);

  /// Adjust quaternion length
  FXQuatd& adjust();

  /// Set quaternion from axis and angle
  void setAxisAngle(const FXVec3d& axis,FXdouble phi=0.0);

  /// Obtain axis and angle from quaternion
  void getAxisAngle(FXVec3d& axis,FXdouble& phi) const;

  /// Set quaternion from roll (x), pitch (y), yaw (z)
  void setRollPitchYaw(FXdouble roll,FXdouble pitch,FXdouble yaw);
  void getRollPitchYaw(FXdouble& roll,FXdouble& pitch,FXdouble& yaw) const;

  /// Set quaternion from yaw (z), pitch (y), roll (x)
  void setYawPitchRoll(FXdouble yaw,FXdouble pitch,FXdouble roll);
  void getYawPitchRoll(FXdouble& yaw,FXdouble& pitch,FXdouble& roll) const;

  /// Set quaternion from roll (x), yaw (z), pitch (y)
  void setRollYawPitch(FXdouble roll,FXdouble yaw,FXdouble pitch);
  void getRollYawPitch(FXdouble& roll,FXdouble& yaw,FXdouble& pitch) const;

  /// Set quaternion from pitch (y), roll (x),yaw (z)
  void setPitchRollYaw(FXdouble pitch,FXdouble roll,FXdouble yaw);
  void getPitchRollYaw(FXdouble& pitch,FXdouble& roll,FXdouble& yaw) const;

  /// Set quaternion from pitch (y), yaw (z), roll (x)
  void setPitchYawRoll(FXdouble pitch,FXdouble yaw,FXdouble roll);
  void getPitchYawRoll(FXdouble& pitch,FXdouble& yaw,FXdouble& roll) const;

  /// Set quaternion from yaw (z), roll (x), pitch (y)
  void setYawRollPitch(FXdouble yaw,FXdouble roll,FXdouble pitch);
  void getYawRollPitch(FXdouble& yaw,FXdouble& roll,FXdouble& pitch) const;

  /// Set quaternion from axes
  void setAxes(const FXVec3d& ex,const FXVec3d& ey,const FXVec3d& ez);

  /// Get quaternion axes
  void getAxes(FXVec3d& ex,FXVec3d& ey,FXVec3d& ez) const;

  /// Obtain local x axis
  FXVec3d getXAxis() const;

  /// Obtain local y axis
  FXVec3d getYAxis() const;

  /// Obtain local z axis
  FXVec3d getZAxis() const;

  /// Exponentiate quaternion
  FXQuatd exp() const;

  /// Take logarithm of quaternion
  FXQuatd log() const;

  /// Invert quaternion
  FXQuatd invert() const;

  /// Invert unit quaternion
  FXQuatd unitinvert() const;

  /// Conjugate quaternion
  FXQuatd conj() const;

  /// Construct quaternion from arc a->b on unit sphere
  FXQuatd& arc(const FXVec3d& a,const FXVec3d& b);

  /// Spherical lerp
  FXQuatd& lerp(const FXQuatd& u,const FXQuatd& v,FXdouble f);

  /// Multiply quaternions
  FXQuatd operator*(const FXQuatd& q) const;

  /// Rotation of a vector by a quaternion
  FXVec3d operator*(const FXVec3d& v) const;
  };


}

#endif
