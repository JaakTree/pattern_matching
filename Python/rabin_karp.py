class RabinKarp:
    """ Implementation of Rabin-Karp algorithm for single pattern matching problem """

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

        pattern_hash = self._hash_fun(pattern)
        substr_hash = self._hash_fun(self.text[:pat_len])
        for i in range(self.text_len - pat_len):
            if pattern_hash == substr_hash:
                if pattern == self.text[i:i + pat_len]:
                    return i

            substr_hash = self._rolling_hash(self.text[i],
                                             self.text[i + pat_len],
                                             substr_hash,
                                             pat_len)

        if pattern_hash == self._hash_fun(self.text[self.text_len-pat_len:]):
            if pattern == self.text[self.text_len-pat_len:]:
                return self.text_len - pat_len

        return -1

    def all_matches(self, pattern):
        """ returns indexes of all matches of a pattern in the text """

        pat_len = len(pattern)
        if pat_len > self.text_len:
            raise ValueError("Pattern length is bigger than text")

        codes =self._preproc()
        pattern_hash = self._hash_fun(pattern, codes)
        substr_hash = self._hash_fun(self.text[:pat_len], codes)
        indexes = []
        k = 0
        for i in range(self.text_len - pat_len):
            if pattern_hash == substr_hash:
                if pattern == self.text[i:i + pat_len]:
                    indexes.append(i)

            substr_hash = self._rolling_hash(self.text[i],
                                             self.text[i + pat_len],
                                             substr_hash,
                                             pat_len,
                                             codes)

        if pattern_hash == self._hash_fun(self.text[self.text_len-pat_len:], codes):
            if pattern == self.text[self.text_len-pat_len:]:
                indexes.append(self.text_len - pat_len)

        return indexes

    def _rolling_hash(self, old_first, new_last, prev_value, str_len, codes):
        return ((prev_value - codes[old_first]) >> 2) + (codes[new_last] << 2*(str_len-1))

    def _preproc(self):
        alphabet = "ACGT"
        codes = dict()
        for i, char in enumerate(alphabet, start=1):
            codes[char] = i

        return codes

    def _hash_fun(self, string, codes):
        hash = 0
        for i in range(len(string)):
            hash += codes[string[i]] << 2*i

        return hash