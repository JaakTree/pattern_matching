import numpy
import pyopencl as cl


class BoyeerMooreHorspoolPOCL:
    """ Implementation of Boyeer-Moore-Horspool algorithm using OpenCL """

    def __init__(self, text, pieces_number=1, alphabet_len=256, device_type=0):
        self.text = text
        self.text_len = len(text)
        self.pieces_num = pieces_number
        self.alphabet_len = alphabet_len
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

        with open("../Pyopencl/bmh/resources/bmh_pocl.cl", "r") as kernel_file:
            kernel_src = kernel_file.read()

        program = cl.Program(context, kernel_src).build()

        if (self.text_len/self.pieces_num <= len(pattern)) or (self.pieces_num > self.text_len):
            raise ValueError("Choose less number of pieces as one piece length less than pattern length "
                             "or pieces number is more than string length")

        # calculate shift table
        table = numpy.array(self._bad_char_table(pattern)).astype(numpy.int)

        # initialize the result array
        matches = numpy.zeros(self.text_len).astype(numpy.int)

        # Create the input (string, pattern, table) strings in device memory and copy data from host
        d_str = cl.Buffer(context, cl.mem_flags.READ_ONLY | cl.mem_flags.COPY_HOST_PTR, hostbuf=self.text.encode())
        d_pat = cl.Buffer(context, cl.mem_flags.READ_ONLY | cl.mem_flags.COPY_HOST_PTR, hostbuf=pattern.encode())
        d_table = cl.Buffer(context, cl.mem_flags.READ_ONLY | cl.mem_flags.COPY_HOST_PTR, hostbuf=table)

        # Create the output (matches) string in device memory
        d_matches = cl.Buffer(context, cl.mem_flags.WRITE_ONLY, matches.nbytes)

        search = program.bmh_search
        search.set_scalar_arg_dtypes([None, None, None, numpy.uint32, numpy.uint32, numpy.uint32, None])
        search(queue, (2*self.pieces_num - 1, ), None, d_str, d_pat, d_table,
               self.text_len, len(pattern), self.pieces_num, d_matches)

        # Wait for the commands to finish before reading back
        queue.finish()

        # Read back the results from the compute device
        cl.enqueue_copy(queue, matches, d_matches)

        return matches

    def _bad_char_table(self, pattern):
        """ calculates amount of shift for each letter """
        pat_len = len(pattern)
        table = [pat_len for _ in range(self.alphabet_len)]
        ord_A = ord('A')
        for i in range(0, pat_len-1):
            indx = ord(pattern[i]) - ord_A
            table[indx] = pat_len - 1 - i
        return table

    def read_data_from(file_name):
        """ read all data from file """
        with open(file_name, 'r') as file:
            string = file.read()
        return string
