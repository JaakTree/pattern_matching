import numpy
import pyopencl as cl


class KnuthMorrisPrattPOCL:
    """ Implementation of Knuth-Morris-Pratt algorithm using OpenCL """

    def __init__(self, text, pieces_number=1, device_type=0):
        self.text = text
        self.text_len = len(text)
        self.pieces_num = pieces_number
        self.device_type = device_type

    def all_matches(self, pattern):
        # Set up OpenCL
        # 0 - means for GPU
        # 1 - means for CPU
        # 2 - means for Accelerator
        # otherwise - some of the devices
        if self.device_type == 0:
            platform = cl.get_platforms()
            devices = platform[0].get_devices(cl.device_type.GPU)
            context = cl.Context(devices)
        elif self.device_type == 1:
            platform = cl.get_platforms()
            devices = platform[0].get_devices(cl.device_type.CPU)
            context = cl.Context(devices)
        elif self.device_type == 2:
            platform = cl.get_platforms()
            devices = platform[0].get_devices(cl.device_type.ACCELERATOR)
            context = cl.Context(devices)
        else:
            context = cl.create_some_context(False)  # don't ask user about platform

        queue = cl.CommandQueue(context)

        with open("../Pyopencl/kmp/resources/kmp_pocl.cl", "r") as kernel_file:
            kernel_src = kernel_file.read()

        program = cl.Program(context, kernel_src).build()

        if (self.text_len/self.pieces_num <= len(pattern)) or (self.pieces_num > self.text_len):
            raise ValueError("Choose less number of pieces as one piece length less than pattern length "
                             "or pieces number is more than string length")

        # calculate prefix function for pattern
        pi = numpy.array(self._prefix_func(pattern)).astype(numpy.int)
        # initialize the result array
        matches = numpy.zeros(self.text_len).astype(numpy.int)

        # Create the input (string, pattern, pi) strings in device memory and copy data from host
        d_text = cl.Buffer(context, cl.mem_flags.READ_ONLY | cl.mem_flags.COPY_HOST_PTR, hostbuf=self.text.encode())
        d_pat = cl.Buffer(context, cl.mem_flags.READ_ONLY | cl.mem_flags.COPY_HOST_PTR, hostbuf=pattern.encode())
        d_pi = cl.Buffer(context, cl.mem_flags.READ_ONLY | cl.mem_flags.COPY_HOST_PTR, hostbuf=pi)
        # Create the output (matches) string in device memory
        d_matches = cl.Buffer(context, cl.mem_flags.WRITE_ONLY, matches.nbytes)
        search = program.kmp_search
        search.set_scalar_arg_dtypes([None, None, None, numpy.uint32, numpy.uint32, numpy.uint32, None])
        search(queue, (2*self.pieces_num - 1, ), None, d_text, d_pat, d_pi,
               self.text_len, len(pattern), self.pieces_num, d_matches)

        # Wait for the commands to finish before reading back
        queue.finish()
        # Read back the results from the compute device
        cl.enqueue_copy(queue, matches, d_matches)

        return matches

    def _prefix_func(self, pattern):
        """ returns prefix function array of the given string """
        str_len = len(pattern)
        pi = [0 for _ in range(str_len)]
        for i in range(1, str_len):
            k = pi[i-1]
            while k > 0 and pattern[k] != pattern[i]:
                k = pi[k-1]
            if pattern[k] == pattern[i]:
                k += 1
            pi[i] = k
        return pi


