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

%rename("adjust!") FXQuatf::adjust();
%rename("arc!")    FXQuatf::arc(const FXVec3f& a,const FXVec3f& b);
%rename("lerp!")   FXQuatf::lerp(const FXQuatf& u,const FXQuatf& v,FXfloat f);

/// Single-precision quaternion
class FXQuatf : public FXVec4f {
public:

  /// Construct
  FXQuatf();

  /// Construct from axis and angle
  FXQuatf(const FXVec3f& axis,FXfloat phi=0.0);

  /// Construct from euler angles yaw (z), pitch (y), and roll (x)
  FXQuatf(FXfloat roll,FXfloat pitch,FXfloat yaw);

  /// Construct quaternion from axes
  FXQuatf(const FXVec3f& ex,const FXVec3f& ey,const FXVec3f& ez);

  /// Construct quaternion from 3x3 matrix
  FXQuatf(const FXMat3f& mat);

  /// Construct from components
  FXQuatf(FXfloat x,FXfloat y,FXfloat z,FXfloat w);

  /// Adjust quaternion length
  FXQuatf& adjust();

  /// Set quaternion from axis and angle
  void setAxisAngle(const FXVec3f& axis,FXfloat phi=0.0f);

  %extend {
    /// Obtain axis and angle from quaternion
    VALUE getAxisAngle() const {
      FXVec3f axis;
      FXfloat phi;
      self->getAxisAngle(axis,phi);
      return rb_ary_new3(2,rb_ary_new3(3,rb_float_new(axis.x),rb_float_new(axis.y),rb_float_new(axis.z)),rb_float_new(phi));
      }
    }

  /// Set quaternion from yaw (z), pitch (y), and roll (x)
  void setRollPitchYaw(FXfloat roll,FXfloat pitch,FXfloat yaw);

  /// Set quaternion from axes
  void setAxes(const FXVec3f& ex,const FXVec3f& ey,const FXVec3f& ez);

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

  %extend {
    /// Obtain yaw, pitch, and roll from quaternion
    VALUE getRollPitchYaw() const {
      FXfloat roll,pitch,yaw;
      self->getRollPitchYaw(roll,pitch,yaw);
      return rb_ary_new3(3,rb_float_new(roll),rb_float_new(pitch),rb_float_new(yaw));
      }

    /// Get quaternion axes
    VALUE getAxes() const {
      FXVec3f ex,ey,ez;
      self->getAxes(ex,ey,ez);
      return rb_ary_new3(3,Qnil,Qnil,Qnil); // FIXME
      }

    /// Multiply quaternions
    FXQuatf operator*(const FXQuatf& other) const { return (*self)*other; }

    // Rotation of a vector by a quaternion
    FXVec3f operator*(const FXVec3f& vec) const { return (*self)*vec; }
    }
  };
