class BoyeerMooreHorspool:
    """ Implementation of Boyer-Moore-Horspool algorithm for single pattern matching problem """

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

        bad_char_table = self._bad_char_table(pattern)
        skip = 0
        while self.text_len - skip >= pat_len:
            i = pat_len - 1
            while self.text[skip + i] == pattern[i]:
                if i == 0:
                    return skip + i

                i -= 1

            skip = skip + self._bad_char_shift(self.text[skip + pat_len - 1], bad_char_table)

        return -1

    def all_matches(self, pattern):
        """ returns indexes of all matches of a pattern in the text """

        pat_len = len(pattern)
        if pat_len > self.text_len:
            raise ValueError("Pattern length is bigger than text")

        bad_char_table = self._bad_char_table(pattern)
        indexes = []
        skip = 0
        while self.text_len - skip >= pat_len:
            i = pat_len - 1
            while self.text[skip + i] == pattern[i]:
                if i == 0:
                    indexes.append(skip + i)
                    break

                i -= 1

            skip = skip + self._bad_char_shift(self.text[skip + pat_len - 1], bad_char_table)

        return indexes

    def _bad_char_table(self, pattern):
        shifts = dict()
        pat_len = len(pattern)
        for i in range(1, pat_len):
            if pattern[pat_len-i-1] not in shifts:
                shifts[pattern[pat_len-i-1]] = i

        shifts['others'] = len(pattern)
        return shifts

    def _bad_char_shift(self, char, shift_table):
        if char in shift_table:
            return shift_table[char]
        else:
            return shift_table['others']
