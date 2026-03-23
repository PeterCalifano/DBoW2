/**
 * File: FORB.h
 * Date: June 2012
 * Author: Dorian Galvez-Lopez
 * Description: functions for ORB descriptors
 * License: see the LICENSE.txt file
 *
 */

#ifndef __D_T_F_ORB__
#define __D_T_F_ORB__

#include "FClass.h"
#include "FeatureTraits.h"
#include <opencv2/core.hpp>
#include <string>
#include <vector>

namespace DBoW2
{
    class FORB;

    template <>
    struct FeatureTraits<FORB>
    {
        using Feature = FORB;
        using Descriptor = cv::Mat;
        static constexpr EFeatureType feature_type = EFeatureType::ORB;
        static constexpr const char *name = "ORB";
        static constexpr bool is_binary = true;
        static constexpr int descriptor_length = 32;
    };
    
    template <>
    struct FeatureTypeTraits<EFeatureType::ORB> : FeatureTraits<FORB>
    {
        using Type = FORB;
    };

    /// Functions to manipulate ORB descriptors
    class FORB : protected FClass
    {
      public:
        typedef FeatureTraits<FORB> Traits;
        /// Feature type
        typedef FeatureTypeTraits<EFeatureType::ORB>::Type FeatureType;
        typedef cv::Mat TDescriptor;
        static constexpr EFeatureType TypeId = Traits::feature_type;

        /// Pointer to a single descriptor
        typedef const TDescriptor *pDescriptor;
        /// Descriptor length (in bytes)
        static const int L = 32;

        /**
         * Calculates the mean value of a set of descriptors
         * @param descriptors
         * @param mean mean descriptor
         */
        static void meanValue(const std::vector<pDescriptor> &descriptors,
                              TDescriptor &mean);

        /**
         * Calculates the distance between two descriptors
         * @param a
         * @param b
         * @return distance
         */
        static double distance(const TDescriptor &a, const TDescriptor &b);

        /**
         * Returns a string version of the descriptor
         * @param a descriptor
         * @return string version
         */
        static std::string toString(const TDescriptor &a);

        /**
         * Returns a descriptor from a string
         * @param a descriptor
         * @param s string version
         */
        static void fromString(TDescriptor &a, const std::string &s);

        /**
         * Returns a mat with the descriptors in float format
         * @param descriptors
         * @param mat (out) NxL 32F matrix
         */
        static void toMat32F(const std::vector<TDescriptor> &descriptors,
                             cv::Mat &mat);

        /**
         * Returns a mat with the descriptors in float format
         * @param descriptors NxL CV_8U matrix
         * @param mat (out) NxL 32F matrix
         */
        static void toMat32F(const cv::Mat &descriptors, cv::Mat &mat);

        /**
         * Returns a matrix with the descriptor in OpenCV format
         * @param descriptors vector of N row descriptors
         * @param mat (out) NxL CV_8U matrix
         */
        static void toMat8U(const std::vector<TDescriptor> &descriptors,
                            cv::Mat &mat);
    };

} // namespace DBoW2

#endif
