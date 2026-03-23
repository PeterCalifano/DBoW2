#pragma once
#include <type_traits>

namespace DBoW2
{
    // TODO update feature classes implementation to use traits for definition of TDescriptor (so that traits work like metadata for the features)
    enum class EFeatureType
    {
        ORB = 0,
        SIFT = 1,
        BRIEF = 2,
        SURF = 3,
        AKAZE = 4,
        BRISK = 5,
        NUM_TYPES
    };

    template <typename>
    struct TDependentFalse : std::false_type
    {
    };

    /**
     * @brief Traits class to define properties of the features used by DBoW2, and to provide type information to the templated structures (TemplatedVocabulary, TemplatedDatabase, ...)
     * 
     * @tparam TFeature 
     */
    template <typename TFeature>
    struct FeatureTraits
    {
        static_assert(TDependentFalse<TFeature>::value, "FeatureTraits not specialized");
    };

    /**
     * @brief Traits class to define the mapping between EFeatureType and the corresponding feature class, and to provide type information to the templated structures (TemplatedVocabulary, TemplatedDatabase, ...)
     * 
     * @tparam T 
     */
    template <EFeatureType T>
    struct FeatureTypeTraits
    {
        static_assert(TDependentFalse<std::integral_constant<EFeatureType, T>>::value,
                      "FeatureTypeTraits not specialized");
    };
}
