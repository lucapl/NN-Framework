#include "tensor/tensor.hpp"
#include <iostream>
#include <cstdlib>

void calculate_strides(Tensor *tensor) {
    for (unsigned int i = 0; i < tensor->rank; ++i) {
        tensor->strides[i] = 1;
        for (unsigned int j = i + 1; j < tensor->rank; ++j) {
            tensor->strides[i] *= tensor->shape[j];
        }
    }
}

void reshape(Tensor *tensor, unsigned int *new_shape, unsigned int new_rank) {
    free(tensor->shape);
    tensor->shape = new_shape;
    tensor->rank = new_rank;

    calculate_strides(tensor);
}

Tensor *create_tensor(float *data, unsigned int *shape, unsigned int rank) {
    Tensor *tensor = new Tensor;//(Tensor *)malloc(sizeof(Tensor));
    tensor->data = data;
    tensor->shape = shape;
    tensor->rank = rank;
    tensor->strides = new unsigned int[rank];//(unsigned int *)malloc(rank * sizeof(unsigned int));

    calculate_strides(tensor);

    return tensor;
}

unsigned int get_flat_index(Tensor *tensor, unsigned int *indices) {
    unsigned int flat_index = 0;
    for (unsigned int i = 0; i < tensor->rank; ++i) {
        flat_index += indices[i] * tensor->strides[i];
    }
    return flat_index;
}

float get_tensor_element(Tensor *tensor, unsigned int *indices) {
    unsigned int flat_index = get_flat_index(tensor, indices);
    //std::cout << "Accessing element " << tensor->data[flat_index] << " at flat index: " << flat_index << std::endl;
    return tensor->data[flat_index];
}

unsigned int total_elements(Tensor *tensor) {
    unsigned int total = 1;
    for (unsigned int i = 0; i < tensor->rank; ++i) {
        total *= tensor->shape[i];
    }
    return total;
}

void destroy_tensor(Tensor *tensor) {
    delete tensor;//free(tensor);
}
