class KnuthMorrisPratt:
    """ Implementation of Knuth-Morris-Pratt algorithm for single pattern matching problem """

    def __init__(self, text):
        self.text = text
        self.text_len = len(text)

    def has_pattern(self, pattern):
        """ returns if there is at least one match of a pattern in the text """

        if len(pattern) > self.text_len:
            raise ValueError("Pattern length is bigger than text")

        if self.first_occurence(pattern) == -1:
            return False

        return True

    def first_occurence(self, pattern):
        """ returns index of first occurences of pattern inside the text """

        pat_len = len(pattern)
        if pat_len > self.text_len:
            raise ValueError("Pattern length is bigger than text")

        k = 0
        index = -1
        pi = self._prefix_func(pattern)
        for i in range(self.text_len):
            while k > 0 and pattern[k] != self.text[i]:
                k = pi[k-1]

            if pattern[k] == self.text[i]:
                k += 1

            if k == pat_len:
                return i - pat_len + 1

        return index

    def all_matches(self, pattern):
        """ returns indexes of all matches of a pattern in the text """

        pat_len = len(pattern)
        if pat_len > self.text_len:
            raise ValueError("Pattern length is bigger than text")

        k = 0
        indexes = []
        pi = self._prefix_func(pattern)
        for i in range(self.text_len):
            while k > 0 and pattern[k] != self.text[i]:
                k = pi[k-1]

            if pattern[k] == self.text[i]:
                k += 1

            if k == pat_len:
                index = i - pat_len + 1
                indexes.append(index)
                k = pi[k-1]

        return indexes

    def _prefix_func(self, string):
        """ returns prefix function array of the given string """

        str_len = len(string)
        pi = [0]*str_len
        for i in range(1, str_len):
            k = pi[i-1]
            while k > 0 and string[k] != string[i]:
                k = pi[k-1]

            if string[k] == string[i]:
                k += 1

            pi[i] = k

        return pi
