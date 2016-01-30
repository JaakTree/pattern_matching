from time import time
import cProfile

from naive import NaiveSearch
from rabin_karp import RabinKarp
from kmp import KnuthMorrisPratt
from boyer_moore_horspool import BoyeerMooreHorspool
from boyer_moore import BoyerMoore


class Measurements:
    """ Implement all needed measurements and illustrate results """

    def __init__(self, text, in_dir, out_dir):
        self.naive = NaiveSearch(text)
        self.rk = RabinKarp(text)
        self.kmp = KnuthMorrisPratt(text)
        self.bmh = BoyeerMooreHorspool(text)
        self.bm = BoyerMoore(text)
        self.data_dir = in_dir
        self.res_dir = out_dir
        self.start = 5
        self.end = 30
        self.step = 5

    def naive_measurements(self):
        res_one, res_two = self._measure(self.naive)
        self._write_res_to("naive.txt", res_one, res_two)

    def rk_measurements(self):
        res_one, res_two = self._measure(self.rk)
        self._write_res_to("rk.txt", res_one, res_two)

    def kmp_measurements(self):
        res_one, res_two = self._measure(self.kmp)
        self._write_res_to("kmp.txt", res_one, res_two)

    def bmh_measurements(self):
        res_one, res_two = self._measure(self.bmh)
        self._write_res_to("bmh.txt", res_one, res_two)

    def bm_measurements(self):
        res_one, res_two = self._measure(self.bm)
        self._write_res_to("bm.txt", res_one, res_two)

    def run_all(self):
        print "Naive algorithm measurements:"
        self.naive_measurements()
        print "Rabin-Karp algorithm measurements:"
        self.rk_measurements()
        print "Knuth-Morris-Pratt algorithm measurements:"
        self.kmp_measurements()
        print "Boyer-Moore-Horspool algorithm measurements:"
        self.bmh_measurements()
        print "Boyer-Moore algorithm measurements:"
        self.bm_measurements()

    def _measure(self, obj):
        results_one = []
        results_two = []
        for size in xrange(self.start, self.end+1, self.step):
            print "size: %d" % (size)
            paterns = self._read_patterns(size)
            interm_res_one = []
            interm_res_two = []
            middle_ind = len(paterns)/2
            for i in xrange(0, middle_ind):
                start = time()
                obj.all_matches(paterns[i])
                end = time()
                interm_res_one.append(end-start)

            for i in xrange(middle_ind, len(paterns)):
                start = time()
                obj.all_matches(paterns[i])
                end = time()
                interm_res_two.append(end-start)

            results_one.append(1.0*sum(interm_res_one)/len(interm_res_one))
            results_two.append(1.0*sum(interm_res_two)/len(interm_res_two))

        return results_one, results_two

    def _read_patterns(self, size):
        file_name = self.data_dir + str(size) + ".txt"
        with open(file_name, 'r') as file:
            patterns = [pat.strip() for pat in file]

        return patterns

    def _write_res_to(self, out_file, res_one, res_two):
        with open(self.res_dir + "/" + out_file, 'w+') as file:
            file.write(" ".join(str(size) for size in xrange(self.start, self.end+1, self.step)) + "\n")
            file.write(" ".join(str(res) for res in res_one) + "\n")
            file.write(" ".join(str(res) for res in res_two) + "\n")

def read_data(file_name):
    """ read all data from file """
    with open(file_name, 'r') as file:
        data = file.read()

    return data

def main():
    genome = read_data("data/processed.txt")
    measurements = Measurements(genome[:100000000], "data/", "results/")
    measurements.run_all()

if __name__ == "__main__":
    cProfile.run('main()')
