#ifndef TENSOR_OPERATIONS_HPP
#define TENSOR_OPERATIONS_HPP
#include "tensor/tensor.hpp"

extern "C"
{
Tensor* add_elementwise_tensors(Tensor* tensor1, Tensor* tensor2, Tensor* new_tensor);
Tensor* multiply_elementwise_tensors(Tensor* tensor1, Tensor* tensor2, Tensor* new_tensor);
Tensor* subtract_elementwise_tensors(Tensor* tensor1, Tensor* tensor2, Tensor* new_tensor);
Tensor* divide_elementwise_tensors(Tensor* tensor1, Tensor* tensor2, Tensor* new_tensor);
}

#endif //TENSOR_OPERATIONS_HPP