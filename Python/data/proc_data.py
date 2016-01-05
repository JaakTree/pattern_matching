from random import randint, choice

def proc_data(in_file, out_file):
    """ read chromosome genome and write genome without additional info to file """
    with open(in_file, 'r') as file:
        data = file.readlines()
        for i in xrange(1, len(data)):
            data[i] = data[i].rstrip().replace("N", "")

    with open(out_file, "w") as file:
        file.write(''.join(data[1:]))

def read_data(file_name):
    """ read all data from file """
    with open(file_name, 'r') as file:
        data = file.read()

    return data

def write_lines_to(file_name, data, mode="w+"):
    """ write info to file line by line """
    with open(file_name, mode) as file:
        for raw in data:
            file.write(str(raw) + "\n")

def cut_pieces(data, size, number=20):
    """ cut fix sized pieces from genome """
    pieces = []
    data_len = len(data)
    for _ in xrange(number):
        index = randint(0, data_len-size-1)
        pieces.append(data[index:index+size])

    return pieces

def write_pieces(data, start=5, end=30, step=5):
    """ write cutted pieces of genome to according files """
    for size in xrange(start, end+1, step):
        pieces = cut_pieces(data, size)
        write_lines_to(str(size) + ".txt", pieces)

def write_random_data(start=5, end=30, step=5, number=20):
    """ generate random genome pieces of particular sizes. Append them to
     according files """
    alphabet = "ACGT"
    for size in xrange(start, end+1, step):
        raws = []
        for __ in xrange(number):
            raw = ''.join(choice(alphabet) for _ in xrange(size))
            raws.append(raw)

        write_lines_to(str(size) + ".txt", raws, "a")

if __name__ == "__main__":
    pass
    #proc_data("Homo_sapiens.GRCh37.68.dna.chromosome.1.fa", "processed.txt")
    #data = _read_data("processed.txt")
    #write_pieces(data)
    #write_random_data()
