/*
 Copyright (C) 2010-2012 Kristian Duske
 
 This file is part of TrenchBroom.
 
 TrenchBroom is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 TrenchBroom is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with TrenchBroom.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __TrenchBroom__MoveObjectsHandle__
#define __TrenchBroom__MoveObjectsHandle__

#include "Model/Picker.h"
#include "Utility/VecMath.h"

using namespace TrenchBroom::Math;

namespace TrenchBroom {
    namespace Model {
        namespace HitType {
            static Type MoveObjectsHandleHit    = 1 << 3;
        }
        
        class MoveObjectsHandleHit : public Hit {
        public:
            typedef enum {
                HAXAxis,
                HAYAxis,
                HAZAxis,
                HAXYPlane,
                HAXZPlane,
                HAYZPlane
            } HitArea;
        private:
            HitArea m_hitArea;
        public:
            MoveObjectsHandleHit(const Vec3f& hitPoint, float distance, HitArea hitArea);
            bool pickable(Filter& filter) const;
            
            inline HitArea hitArea() const {
                return m_hitArea;
            }
        };
    }

    namespace Controller {
        class MoveObjectsHandle {
        protected:
            float m_axisLength;
            float m_planeRadius;
            Vec3f m_position;
            bool m_locked;
            Vec3f m_xAxis, m_yAxis, m_zAxis;
            bool m_hit;
            Model::MoveObjectsHandleHit::HitArea m_hitArea;

            Model::MoveObjectsHandleHit* pickAxis(const Ray& ray, Vec3f& axis, Model::MoveObjectsHandleHit::HitArea hitArea);
            Model::MoveObjectsHandleHit* pickPlane(const Ray& ray, const Vec3f& normal, const Vec3f& axis1, const Vec3f& axis2, Model::MoveObjectsHandleHit::HitArea hitArea);
            Model::MoveObjectsHandleHit* selectHit(Model::MoveObjectsHandleHit* closestHit, Model::MoveObjectsHandleHit* hit);
        public:
            MoveObjectsHandle(float axisLength, float planeRadius);
            
            void axes(const Vec3f& origin, Vec3f& xAxis, Vec3f& yAxis, Vec3f& zAxis);

            Model::MoveObjectsHandleHit* pick(const Ray& ray);
            
            inline float axisLength() const {
                return m_axisLength;
            }
            
            inline float planeRadius() const {
                return m_planeRadius;
            }
            
            inline const Vec3f& position() const {
                return m_position;
            }
            
            inline void setPosition(const Vec3f& position) {
                m_position = position;
            }

            inline void lock() {
                m_locked = true;
            }
            
            inline void unlock() {
                m_locked = false;
            }
            
            inline bool hit() const {
                return m_hit;
            }
            
            inline Model::MoveObjectsHandleHit::HitArea hitArea() const {
                return m_hitArea;
            }
        };
    }
}

#endif /* defined(__TrenchBroom__MoveObjectsHandle__) */
