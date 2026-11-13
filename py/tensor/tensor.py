from ctypes import *
import os
import itertools

tensor_lib = cdll.LoadLibrary(os.path.join(os.environ['PY_TENSOR_LIB'], "libtensor.so"))

print(tensor_lib.__dict__)

class TENSOR(Structure):
    _fields_ = [("shape", POINTER(c_uint)),
                ("rank", c_uint),
                ("strides", POINTER(c_uint)),
                ("data", POINTER(c_float))]

tensor_p = POINTER(TENSOR)

tensor_lib.create_tensor.argtypes = [c_void_p, POINTER(c_uint), c_uint]
tensor_lib.create_tensor.restype = tensor_p

tensor_lib.destroy_tensor.argtypes = [tensor_p]
tensor_lib.destroy_tensor.restype = None

tensor_lib.get_tensor_element.argtypes = [tensor_p, POINTER(c_uint)]
tensor_lib.get_tensor_element.restype = c_float

tensor_lib.add_elementwise_tensors.argtypes = [tensor_p, tensor_p]
tensor_lib.add_elementwise_tensors.restype = tensor_p

class Tensor:
    def __init__(self, data, shape):
        self.shape = shape

        self.data_array = (c_float * len(data))(*data)
        self.shape_array = (c_uint*len(shape))(*shape)

        self.tensor = tensor_lib.create_tensor(cast(self.data_array, c_void_p), self.shape_array, c_uint(len(shape)))

    @classmethod
    def from_tensor_ptr(cls, tensor_ptr):
        tensor = cls.__new__(cls)
        tensor.tensor_ptr = tensor_ptr
        # Retrieve shape from the C++ Tensor object
        shape_array = (c_uint * 10)()  # Assuming a maximum rank of 10 for simplicity
        tensor.shape = [shape_array[i] for i in range(len(shape_array)) if shape_array[i] != 0]
        return tensor

    @property
    def rank(self):
        return len(self.shape)

    def __del__(self):
        ptr = getattr(self, "tensor_ptr", None)

        if ptr:
            tensor_lib.destroy_tensor(ptr)
            self.tensor_ptr = None

    def __getitem__(self, index):
        index_array = (c_uint * len(self.shape))(*index)
        return tensor_lib.get_tensor_element(self.tensor_ptr, index_array)

    def __setitem__(self, index, value):
        index_array = (c_uint * len(self.shape))(*index)
        tensor_lib.set_tensor_element(self.tensor_ptr, index_array, c_float(value))

    def __str__(self):
        result = "Tensor(shape={}, data=".format(self.shape)
        end_line = False
        result += "[" * (self.rank - 1)
        for index in itertools.product(*[range(dim) for dim in self.shape]):
            if end_line:
                result += "],\n"
            elif index[-1] == 0:
                result += "["
            else:
                result += ", "
            result += str(self[index])
            end_line = index[-1] == self.shape[-1] - 1
        result += "]" * (self.rank - 1)
        result += ")"
        return result

    def __add__(self, other):
        if isinstance(other, Tensor):
            return tensor_lib.add_elementwise_tensors(self.tensor_ptr, other.tensor_ptr)
        else:
            raise TypeError("Unsupported operand type for +: 'Tensor' and '{}'".format(type(other).__name__))

    #def get_data(self):


if __name__ == "__main__":
    print("Testing Tensor class...")
    tensor1 = Tensor(list(range(10))[::-1], [1,2,5])
    print(tensor1)
    tensor2 = Tensor(list(range(10)), [1,2,5])
    print(tensor2)

    print(tensor1 + tensor2)

    del tensor1
    del tensor2
    print("Finishing...")
    