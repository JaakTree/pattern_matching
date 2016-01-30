import matplotlib.pyplot as plt

class Plot:
    """ Plot all results """

    def __init__(self, res_dir):
        self.res_dir = res_dir
        self.start = 5
        self.end = 30
        self.step = 5

    def plot_naive(self):
        x, res_one, res_two = self._read_data("naive.txt")
        self._plot_pair(x, res_one, res_two, self.res_dir + "img/naive.png", "Naive method")

    def plot_rk(self):
        x, res_one, res_two = self._read_data("rk.txt")
        self._plot_pair(x, res_one, res_two, self.res_dir + "img/rk.png", "Rabin-Karp")

    def plot_kmp(self):
        x, res_one, res_two = self._read_data("kmp.txt")
        self._plot_pair(x, res_one, res_two, self.res_dir + 'img/kmp.png', "Knuth-Morris-Pratt")

    def plot_bmh(self):
        x, res_one, res_two = self._read_data("bmh.txt")
        self._plot_pair(x, res_one, res_two, self.res_dir + 'img/bmh.png', "Boyer-Moore-Horspool")

    def plot_bm(self):
        x, res_one, res_two = self._read_data("bm.txt")
        self._plot_pair(x, res_one, res_two, self.res_dir + "img/bm.png", "Boyer-Moore")

    def plot_all(self):
        self.plot_naive()
        self.plot_rk()
        self.plot_kmp()
        self.plot_bmh()
        self.plot_bm()

    def _plot_pair(self, x, y1, y2, save_to, title, x_name="Pattern length", y_name="Time, sec"):
        x_range = self.end
        y_range = 1.25 * max(max(y1), max(y2))
        plt.plot(x, y1, 'r-', label="Python version")
        plt.plot(x, y2, 'g-', label="C++ version")
        plt.axis([self.step, x_range, 0, y_range])
        if x_name:
            plt.xlabel(x_name)
        if y_name:
            plt.ylabel(y_name)

        plt.title(title)
        plt.legend()
        plt.savefig(save_to)
        plt.show()

    def _plot_average(self, x, y1, y2, save_to, x_name="Pattern length", y_name="Time, sec"):
        x_range = self.end
        y_range = 1.25 * max(max(y1), max(y2))
        y = []
        for pair in zip(y1, y2):
            y.append((pair[0]+pair[1])/2.0)

        if x_name:
            plt.xlabel(x_name)
        if y_name:
            plt.ylabel(y_name)

        plt.axis([self.step, x_range, 0, y_range])
        plt.plot(x, y, 'r-')
        plt.savefig(save_to)
        plt.show()

    def _read_data(self, file_name):
        path = self.res_dir + file_name
        with open(path, 'r') as file:
            x = [int(elem) for elem in file.readline().rstrip().split()]
            res_exist = [float(elem) for elem in file.readline().rstrip().split()]
            res_rnd = [float(elem) for elem in file.readline().rstrip().split()]

        return x, res_exist, res_rnd

if __name__ == "__main__":
    pl = Plot("results/newest/5-30/")
    pl.plot_all()


