#include "tensor/tensor_operations.hpp"
#include <iostream>
#include <cstdlib>

bool are_shapes_equal(Tensor* tensor1, Tensor* tensor2) {
    if (tensor1->rank != tensor2->rank) {
        return false;
    }
    for (unsigned int i = 0; i < tensor1->rank; ++i) {
        if (tensor1->shape[i] != tensor2->shape[i]) {
            return false;
        }
    }
    return true;
}

Tensor* op_elementwise_tensors(Tensor* tensor1, Tensor* tensor2, float (*operation)(float, float), Tensor* new_tensor) {
    if(!are_shapes_equal(tensor1, tensor2)){
        std::cerr << "Shapes of Tensors should be equal" << std::endl;
        return nullptr;
    }

    unsigned int tensors_size = total_elements(tensor1);

    float* data = new float[tensors_size];//malloc(sizeof(float)*tensor_sizes);
    for (unsigned int i = 0; i < tensors_size; i++){
        data[i] = operation(tensor1->data[i], tensor2->data[i]);
    }

    unsigned int rank = tensor1->rank;

    unsigned int* shape = new unsigned int[rank];
    for (unsigned int i = 0; i < rank; i++){
        shape[i] = tensor1->shape[i];
    }

    new_tensor = create_tensor(data, shape, rank);
    return new_tensor;
}


Tensor* add_elementwise_tensors(Tensor* tensor1, Tensor* tensor2, Tensor* new_tensor) {
    return op_elementwise_tensors(tensor1, tensor2, [](float a, float b) { return a + b; });
}

Tensor* multiply_elementwise_tensors(Tensor* tensor1, Tensor* tensor2, Tensor* new_tensor) {
    return op_elementwise_tensors(tensor1, tensor2, [](float a, float b) { return a * b; });
}

Tensor* subtract_elementwise_tensors(Tensor* tensor1, Tensor* tensor2, Tensor* new_tensor) {
    return op_elementwise_tensors(tensor1, tensor2, [](float a, float b) { return a - b; });
}

Tensor* divide_elementwise_tensors(Tensor* tensor1, Tensor* tensor2, Tensor* new_tensor) {
    return op_elementwise_tensors(tensor1, tensor2, [](float a, float b) { return a / b; });
}
