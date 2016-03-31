from random import randint, choice


def process_data(in_file, out_file):
    """ read chromosome genome and write genome without additional info to file """
    with open(in_file, 'r') as file:
        genome = file.readlines()
        for i in range(1, len(genome)):
            genome[i] = genome[i].rstrip().replace("N", "")

    with open(out_file, "w") as file:
        file.write(''.join(genome[1:]))


def read_from(file_name):
    """ read all data from file """
    with open(file_name, 'r') as file:
        data = file.read()
    return data


def write_lines_to(file_name, data, mode="w+"):
    """ write info to file line by line """
    with open(file_name, mode) as file:
        for raw in data:
            file.write(str(raw) + "\n")


def cut_pieces(data, size, number=25):
    """ cut fix sized pieces from genome """
    pieces = []
    data_len = len(data)
    for _ in range(number):
        index = randint(0, data_len-size-1)
        pieces.append(data[index:index+size])
    return pieces


def write_pieces(data, start=25, end=200, step=25):
    """ write cutted pieces of genome to according files """
    for size in range(start, end+1, step):
        pieces = cut_pieces(data, size)
        write_lines_to(str(size) + ".txt", pieces)


def write_random_data(start=25, end=200, step=25, number=25):
    """ generate random genome pieces of particular sizes. Append them to
     according files """
    alphabet = "ACGT"
    for size in range(start, end+1, step):
        raws = []
        for __ in range(number):
            raw = ''.join(choice(alphabet) for _ in range(size))
            raws.append(raw)

        write_lines_to(str(size) + ".txt", raws, "a")


if __name__ == "__main__":
    #process_data("Homo_sapiens.GRCh37.68.dna.chromosome.1.fa", "processed.txt")
    data = read_from("processed.txt")
    write_pieces(data, 25, 200, 25)
    write_random_data(25, 200, 25)
