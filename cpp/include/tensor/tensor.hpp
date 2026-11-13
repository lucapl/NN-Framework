#ifndef TENSOR_HPP
#define TENSOR_HPP

extern "C"
{
    typedef struct {
        unsigned int *shape;
        unsigned int rank;
        unsigned int *strides;
        float *data;
    } Tensor;

    void reshape(Tensor *tensor, unsigned int *new_shape, unsigned int new_rank);
    Tensor *create_tensor(float *data, unsigned int *shape, unsigned int rank);
    float get_tensor_element(Tensor *tensor, unsigned int *indices);
    unsigned int *get_tensor_shape(Tensor *tensor);
    void set_tensor_element(Tensor *tensor, unsigned int *indices, float value);
    void destroy_tensor(Tensor *tensor);
    unsigned int total_elements(Tensor *tensor);
}

#endif //TENSOR_HPP
