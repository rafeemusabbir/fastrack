/*
 * Copyright (c) 2018, The Regents of the University of California (Regents).
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *
 *    2. Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *
 *    3. Neither the name of the copyright holder nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS AS IS
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Please contact the author(s) of this library if you have any questions.
 * Authors: David Fridovich-Keil   ( dfk@eecs.berkeley.edu )
 */

///////////////////////////////////////////////////////////////////////////////
//
// Cylinder for tracking error bound. This can occur when dynamics decouple
// in z vs x/y. Cylinders are parameterized by radius and half vertical height.
//
///////////////////////////////////////////////////////////////////////////////

#define FASTRACK_BOUND_CYLINDER_H

#include <fastrack/bound/tracking_bound.h>
#include <fastrack/utils/types.h>

#include <fastrack_srvs/TrackingBoundCylinder.h>
#include <fastrack_srvs/TrackingBoundCylinderResponse.h>

namespace fastrack {
namespace bound {

struct Cylinder
    : public TrackingBound<fastrack_srvs::TrackingBoundCylinder::Response> {
  // Radius.
  double r;

  // Half vertical extent.
  double z;

  // Initialize from vector. Assume laid out as: [r, z].
  bool Initialize(const std::vector<double>& params) {
    if (params.size() != 2) {
      ROS_ERROR("Cylinder: params were incorrect size.");
      return false;
    }

    r = params[0];
    z = params[1];
    return true;
  }

  // Convert from service response type SR.
  void FromRos(const fastrack_srvs::TrackingBoundCylinder::Response& res) {
    r = res.r;
  }

  // Convert to service response.
  fastrack_srvs::TrackingBoundCylinder::Response ToRos() const {
    fastrack_srvs::TrackingBoundCylinder::Response res;
    res.r = r;

    return res;
  }

  // Visualize.
  void Visualize(const ros::Publisher& pub, const std::string& frame) const {
    visualization_msgs::Marker m;
    m.ns = "bound";
    m.header.frame_id = frame;
    m.header.stamp = ros::Time::now();
    m.id = 0;
    m.type = visualization_msgs::Marker::CYLINDER;
    m.action = visualization_msgs::Marker::ADD;
    m.color.a = 0.3;
    m.color.r = 0.5;
    m.color.g = 0.1;
    m.color.b = 0.5;
    m.scale.x = 2.0 * r;
    m.scale.y = 2.0 * r;
    m.scale.z = 2.0 * z;

    pub.publish(m);
  }

}; //\struct Cylinder

} //\namespace bound
} //\namespace fastrack

#endif
