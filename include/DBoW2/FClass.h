/**
 * File: FClass.h
 * Date: November 2011
 * Author: Dorian Galvez-Lopez
 * Description: generic FClass to instantiate templated classes
 * License: see the LICENSE.txt file
 *
 */

#ifndef __D_T_FCLASS__
#define __D_T_FCLASS__

#include <opencv2/core.hpp>
#include <string>
#include <vector>

namespace DBoW2
{

    // TODO change design: TemplateVocabulary is already templated. It knows the type of descriptor and the type of feature class, hence FClass can be easily replaced by a concept to impose required methods that any feature class should have.

    /// Generic class to encapsulate functions to manage descriptors.
    /**
     * This class must be inherited. Derived classes can be used as the
     * parameter TFeature when creating Templated structures
     * (TemplatedVocabulary, TemplatedDatabase, ...)
     */
    class FClass
    {
        class TDescriptor;
        typedef const TDescriptor *pDescriptor;

        /**
         * Calculates the mean value of a set of descriptors
         * @param descriptors
         * @param mean mean descriptor
         */
        // BUG: pure virtual method overloaded in derived classes as static? Does not make sense. Rework
        virtual void meanValue(const std::vector<pDescriptor> &descriptors,
                               TDescriptor &mean) = 0;

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
