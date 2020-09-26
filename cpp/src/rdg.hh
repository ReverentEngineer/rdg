/**
 * @file rdg.hh
 *
 * @brief Public C++ interface for librdg.
 */

#ifndef __RDG_HH__
#define __RDG_HH__

#include <string>

#include "rdg.h"

/**
 * @defgroup rdgpp librdg++
 * Documentation for C++ interface to librdg
 * @{
 */

/**
 * @brief A regex (regula expression) data generator 
 */
class RDG {
  public:

    /**
     * @brief Constructs a regex data generator
     *
     * @param expression A regular expression (within the defined subset)
     */
    RDG(const std::string& expression);
    virtual ~RDG();

    /**
     * @brief Generates the next result from the data generator
     *
     * @throws std::length_error When generate is called with no remaining
     * permutations.
     *
     * @return A string containing the permutation
     */
    std::string generate();

    /**
     * @brief Gets the number of permutations.
     *
     * @return Number of permutations
     */
    size_t permutations() const;

  private:

    /** Instance of C representation of the regex data generator. **/
    rdg* m_rdg;
};

/**
 * @}
 */

#endif /* __RDG_HH__ */
