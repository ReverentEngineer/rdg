#include "rdg.hh"

RDG::RDG(const std::string& expression) {
  m_rdg = rdg_new(expression.c_str());
  if (m_rdg == NULL) {
    throw std::domain_error("Could not generate data using regular expression.");
  }
}

RDG::~RDG() {
  if (m_rdg) {
    rdg_free(m_rdg);
  }
}

std::string
RDG::generate() {
  const unsigned char *data = NULL;
  size_t size = 0;
  if (!rdg_generate(&data, &size, m_rdg)) {
    throw std::length_error("There are no more remaining data permutations.");
  } 
  return std::string(data, data + size);
}

size_t
RDG::permutations() const {
  return rdg_permutations(m_rdg);
}
