/**
 * File: FBrief.h
 * Date: November 2011
 * Author: Dorian Galvez-Lopez
 * Description: functions for BRIEF descriptors
 * License: see the LICENSE.txt file
 *
 */

#ifndef __D_T_F_BRIEF__
#define __D_T_F_BRIEF__

#include <bitset>
#include <opencv2/core.hpp>
#include <string>
#include <vector>

#include "FClass.h"
#include "FeatureTraits.h"

namespace DBoW2
{

    class FBrief;

    template <>
    struct FeatureTraits<FBrief>
    {
        using Feature = FBrief;
        using Descriptor = std::bitset<256>;
        static constexpr EFeatureType feature_type = EFeatureType::BRIEF;
        static constexpr const char *name = "BRIEF";
        static constexpr bool is_binary = true;
        static constexpr int descriptor_length = 256;
    };

    template <>
    struct FeatureTypeTraits<EFeatureType::BRIEF>
        : FeatureTraits<FBrief>
    {
        using Type = FBrief;
    };

    /// Functions to manipulate BRIEF descriptors
    class FBrief : protected FClass
    {
      public:
        typedef FeatureTraits<FBrief> Traits;
        typedef FeatureTypeTraits<EFeatureType::BRIEF>::Type FeatureType;
        static constexpr EFeatureType TypeId = Traits::feature_type;
        
        static const int L = 256; // Descriptor length (in bits)
        typedef std::bitset<L> TDescriptor;
        typedef const TDescriptor *pDescriptor;

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
    };

} // namespace DBoW2

#endif
