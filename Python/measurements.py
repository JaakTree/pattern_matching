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
        self.start = 50
        self.end = 300
        self.step = 50

    def naive_measurements(self):
        results = self._measure(self.naive)
        self._write_res_to("naive.txt", results)

    def rk_measurements(self):
        results = self._measure(self.rk)
        self._write_res_to("rk.txt", results)

    def kmp_measurements(self):
        results = self._measure(self.kmp)
        self._write_res_to("kmp.txt", results)

    def bmh_measurements(self):
        results = self._measure(self.bmh)
        self._write_res_to("bmh.txt", results)

    def bm_measurements(self):
        results = self._measure(self.bm)
        self._write_res_to("bm.txt", results)

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
        results = []
        for size in xrange(self.start, self.end+1, self.step):
            print "size: %d" % (size)
            paterns = self._read_patterns(size)
            interm_res = []
            for i in xrange(0, len(paterns)):
                start = time()
                obj.all_matches(paterns[i])
                end = time()
                interm_res.append(end-start)

            results.append(1.0*sum(interm_res)/len(interm_res))

        return results

    def _read_patterns(self, size):
        file_name = self.data_dir + str(size) + ".txt"
        with open(file_name, 'r') as file:
            patterns = [pat.strip() for pat in file]

        return patterns

    def _write_res_to(self, out_file, results):
        with open(self.res_dir + "/" + out_file, 'w+') as file:
            file.write(" ".join(str(size) for size in xrange(self.start, self.end+1, self.step)) + "\n")
            file.write(" ".join(str(res) for res in results) + "\n")

def read_data(file_name):
    """ read all data from file """
    with open(file_name, 'r') as file:
        data = file.read()

    return data

def main():
    genome = read_data("data/processed.txt")
    measurements = Measurements(genome, "data/", "results/")
    #measurements.run_all()
    measurements.rk_measurements()

if __name__ == "__main__":
    cProfile.run('main()')