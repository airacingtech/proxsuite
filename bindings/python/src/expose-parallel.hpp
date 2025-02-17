//
// Copyright (c) 2023 INRIA
//

#include <proxsuite/proxqp/dense/wrapper.hpp>
#include <proxsuite/proxqp/sparse/wrapper.hpp>
#include <proxsuite/proxqp/parallel/qp_solve.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h> // For binding STL containers

PYBIND11_MAKE_OPAQUE(std::vector<proxsuite::proxqp::dense::QP<double>>)

namespace proxsuite {
namespace proxqp {
using proxsuite::linalg::veg::isize;

namespace dense {
namespace python {

template<typename T>
void
solveDenseQpParallel(pybind11::module_ m)
{
  pybind11::bind_vector<std::vector<proxsuite::proxqp::dense::QP<T>>>(
    m, "VectorQP");

  m.def("solve_in_parallel",
        pybind11::overload_cast<std::vector<proxqp::dense::QP<T>>&,
                                const optional<size_t>>(&solve_in_parallel<T>),
        "Function for solving a list of dense QPs in parallel.",
        pybind11::arg_v("qps", "List of initialized dense Qps."),
        pybind11::arg_v("num_threads",
                        nullopt,
                        "number of threads used for the computation."));

  m.def(
    "solve_in_parallel",
    pybind11::overload_cast<proxqp::dense::BatchQP<T>&, const optional<size_t>>(
      &solve_in_parallel<T>),
    "Function for solving a list of dense QPs in parallel.",
    pybind11::arg_v("qps", "List of initialized dense Qps."),
    pybind11::arg_v(
      "num_threads", nullopt, "number of threads used for the computation."));
}

} // namespace python
} // namespace dense

namespace sparse {
namespace python {
template<typename T, typename I>
void
solveSparseQpParallel(pybind11::module_ m)
{
  m.def(
    "solve_in_parallel",
    pybind11::overload_cast<proxqp::sparse::BatchQP<T, I>&,
                            const optional<size_t>>(&solve_in_parallel<T, I>),
    "Function for solving a list of sparse QPs in parallel.",
    pybind11::arg_v("qps", "List of initialized sparse Qps."),
    pybind11::arg_v(
      "num_threads", nullopt, "number of threads used for the computation."));
}

} // namespace python
} // namespace sparse

} // namespace proxqp
} // namespace proxsuite
