/***********************************************************************
 * FXRuby -- the Ruby language bindings for the FOX GUI toolkit.
 * Copyright (c) 2001-2009 by Lyle Johnson. All Rights Reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * For further information please contact the author by e-mail
 * at "lyle@lylejohnson.name".
 ***********************************************************************/

%rename("adjust!") FXQuatd::adjust();
%rename("arc!")    FXQuatd::arc(const FXVec3d& a,const FXVec3d& b);
%rename("lerp!")   FXQuatd::lerp(const FXQuatd& u,const FXQuatd& v,FXdouble f);

/// Double-precision quaternion
class FXQuatd : public FXVec4d {
public:

  /// Constructors
  FXQuatd();

  /// Copy constructor
  FXQuatd(const FXQuatd& q);

  /// Construct from components
  FXQuatd(FXdouble xx,FXdouble yy,FXdouble zz,FXdouble ww);

  /// Construct from array of doubles
  FXQuatd(const FXdouble v[]);

  /// Construct from axis and angle
  FXQuatd(const FXVec3d& axis,FXdouble phi=0.0);

  /// Construct from euler angles yaw (z), pitch (y), and roll (x)
  FXQuatd(FXdouble roll,FXdouble pitch,FXdouble yaw);

  /// Construct quaternion from axes
  FXQuatd(const FXVec3d& ex,const FXVec3d& ey,const FXVec3d& ez);

  /// Adjust quaternion length
  FXQuatd& adjust();

  /// Set quaternion from axis and angle
  void setAxisAngle(const FXVec3d& axis,FXdouble phi=0.0);

  %extend {
    /// Obtain axis and angle from quaternion
    VALUE getAxisAngle() const {
      FXVec3d axis;
      FXdouble phi;
      self->getAxisAngle(axis,phi);
      return rb_ary_new3(2,rb_ary_new3(3,rb_float_new(axis.x),rb_float_new(axis.y),rb_float_new(axis.z)),rb_float_new(phi));
      }
    }

  /// Set quaternion from yaw (z), pitch (y), and roll (x)
  void setRollPitchYaw(FXdouble roll,FXdouble pitch,FXdouble yaw);

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

  %extend {
    /// Obtain yaw, pitch, and roll from quaternion
    VALUE getRollPitchYaw() const {
      FXdouble roll,pitch,yaw;
      self->getRollPitchYaw(roll,pitch,yaw);
      return rb_ary_new3(3,rb_float_new(roll),rb_float_new(pitch),rb_float_new(yaw));
      }

    /// Multiply quaternions
    FXQuatd operator*(const FXQuatd& other) const { return (*self)*other; }

    // Rotation of a vector by a quaternion
    FXVec3d operator*(const FXVec3d& vec) const { return (*self)*vec; }
    }

  /// Set quaternion from axes
  void setAxes(const FXVec3d& ex,const FXVec3d& ey,const FXVec3d& ez);

  /// Get quaternion axes
  %extend {
    VALUE getAxes() const {
      FXVec3d ex,ey,ez;
      self->getAxes(ex,ey,ez);
      return rb_ary_new3(3,Qnil,Qnil,Qnil);
    }
  }

  /// Obtain local x axis
  FXVec3d getXAxis() const;

  /// Obtain local y axis
  FXVec3d getYAxis() const;

  /// Obtain local z axis
  FXVec3d getZAxis() const;
  };

