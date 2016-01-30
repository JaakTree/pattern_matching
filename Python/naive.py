class NaiveSearch:
    """ Implementation of naive search algorithm for single pattern matching problem """

    def __init__(self, text):
        self.text = text
        self.text_len = len(text)

    def has_pattern(self, pattern):
        """ returns if there is at least one match of a pattern in the text """

        pat_len = len(pattern)
        if pat_len > self.text_len:
            raise ValueError("Pattern length is bigger than text")

        if self.first_occurence(pattern) == -1:
            return False

        return True

    def first_occurence(self, pattern):
        """ returns index of first occurences of pattern inside the text """

        pat_len = len(pattern)
        if pat_len > self.text_len:
            raise ValueError("Pattern length is bigger than text")

        i = 0
        while i + pat_len <= self.text_len:
            j = 0
            while j < pat_len:
                if self.text[i+j] != pattern[j]:
                    break
                j += 1
            if j == pat_len:
                return i
            i += 1

        return -1

    def all_matches(self, pattern):
        """ returns indexes of all matches of a pattern in the text """

        pat_len = len(pattern)
        if pat_len > self.text_len:
            raise ValueError("Pattern length is bigger than text")

        indexes = []
        i = 0
        while i + pat_len <= self.text_len:
            j = 0
            while j < pat_len:
                if self.text[i+j] != pattern[j]:
                    break
                j += 1
            if j == pat_len:
                indexes.append(i)
            i += 1

        return indexes
