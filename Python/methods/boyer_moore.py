class BoyerMoore:
    """ Implementation of Boyer-Moore algorithm for single pattern matching problem """

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
        L = self._good_suffix_table_one(pattern)
        H = self._good_suffix_table_two(pattern)

        pat_end_ind = pat_len - 1
        prev_end = -1
        # prev_end - previous index of pattern end relative to text (for Galil's rule)
        # p - index of char in pattern
        # t - index of char in text
        while pat_end_ind < self.text_len:
            p = pat_len - 1
            t = pat_end_ind
            while p >= 0 and t > prev_end and pattern[p] == self.text[t]:
                p -= 1
                t -= 1
            if p == -1 or t == prev_end:  # Matched or holds Galil's rule
                return pat_end_ind - pat_len + 1
                pat_end_ind += pat_len - H[1] if pat_len > 1 else 1
            else:
                char_shift = self._bad_char_shift(self.text[t], bad_char_table)
                if p+1 == pat_len:
                    suffix_shift = 1
                elif L[p] == -1:
                    suffix_shift = pat_len - H[p+1]
                else:
                    suffix_shift = pat_len - L[p]
                shift = max(char_shift, suffix_shift)
                prev_end = pat_end_ind if shift >= p+1 else prev_end  #update parameter for Galil's rule
                pat_end_ind += shift

        return -1

    def all_matches(self, pattern):
        """ returns indexes of all matches of a pattern in the text """

        pat_len = len(pattern)
        if pat_len > self.text_len:
            raise ValueError("Pattern length is bigger than text")

        bad_char_table = self._bad_char_table(pattern)
        L = self._good_suffix_table_one(pattern)
        H = self._good_suffix_table_two(pattern)
        indexes = []

        pat_end_ind = pat_len - 1
        prev_end = -1
        # prev_end - previous index of pattern end relative to text (for Galil's rule)
        # p - index of char in pattern
        # t - index of char in text
        while pat_end_ind < self.text_len:
            p = pat_len - 1
            t = pat_end_ind
            while p >= 0 and t > prev_end and pattern[p] == self.text[t]:
                p -= 1
                t -= 1
            if p == -1 or t == prev_end:  # Matched or holds Galil's rule
                indexes.append(pat_end_ind - pat_len + 1)
                pat_end_ind += pat_len - H[1] if pat_len > 1 else 1
            else:
                char_shift = self._bad_char_shift(self.text[t], bad_char_table)
                if p+1 == pat_len:
                    suffix_shift = 1
                elif L[p] == -1:
                    suffix_shift = pat_len - H[p+1]
                else:
                    suffix_shift = pat_len - L[p]
                shift = max(char_shift, suffix_shift)
                prev_end = pat_end_ind if shift >= p+1 else prev_end  #update parameter for Galil's rule
                pat_end_ind += shift

        return indexes

    def _bad_char_table(self, pattern):
        shifts = dict()
        pat_len = len(pattern)
        for i in range(1, pat_len):
            if pattern[pat_len-i-1] not in shifts:
                shifts[pattern[pat_len-i-1]] = i - 1

        shifts['others'] = len(pattern) - 1
        return shifts

    def _bad_char_shift(self, char, shift_table):
        if char in shift_table:
            return shift_table[char]
        else:
            return shift_table['others']

    def _matched_len(self, string, idx1, idx2):
        """ returns an overlap match length of two substrings of a given string beginning at idx1 and idx2 """

        str_len = len(string)
        if idx1 == idx2:
            return str_len - idx1
        counter = 0
        while idx1 < str_len and idx2 < str_len and string[idx1] == string[idx2]:
            counter += 1
            idx1 += 1
            idx2 += 1

        return counter

    def _preprocessing(self, pattern):
        """ returns array i-th element of which is the length of the substring of given string
        which begins at i-th position and simulataniously is a prefix of the string """

        pat_len = len(pattern)
        if pat_len == 1:
            return [1]

        Z = [0 for _ in pattern]
        Z[0] = pat_len
        Z[1] = self._matched_len(pattern, 0, 1)
        for i in range(2, 1 + Z[1]):
            Z[i] = Z[1] - i + 1
        # Defines boundaries for z-box
        left = 0
        right = 0
        for i in range(2 + Z[1], pat_len):
            if i <= right: # z-box contains i
                k = i - left
                b = Z[k]
                a = right - i + 1
                if b < a: # b ends within existing z-box
                    Z[i] = b
                else: # b ends at or after the end of the z-box, we need to do an explicit match to the right of the z-box
                    Z[i] = b + self._matched_len(pattern, a, right+1)
                    left = i
                    right = i + Z[i] - 1
            else: # z-box does not contain i
                Z[i] = self._matched_len(pattern, 0, i)
                if Z[i] > 0:
                    left = i
                    right = i + Z[i] - 1
        return Z

    def _good_suffix_table_one(self, pattern):
        """ returns L-matrix. For each i, L[i] is the largest position less than n such that string P[i..n]
        matches a suffix of P[1..L[i]]. In the case that L[i] = -1, the second shift table is used. """

        pat_len = len(pattern)
        L = [-1 for _ in pattern]
        preproc_array = self._preprocessing(pattern[::-1])
        preproc_array.reverse()
        for j in range(0, pat_len-1):
            i = pat_len - preproc_array[j]
            if i != pat_len:
                L[i] = j

        return L

    def _good_suffix_table_two(self, pattern):
        """ returns H-matrix where H[i] is the length of the largest suffix of P[i..n]
         that is also a prefix of P, if one exists. If none exists, let H[i] be zero. """

        H = [0 for _ in pattern]
        preproc_array = self._preprocessing(pattern)
        longest = 0
        prep_ar_len = len(preproc_array)
        for i in range(0, prep_ar_len):
            if preproc_array[prep_ar_len-i-1] == i+1:
                longest = max(preproc_array[prep_ar_len-i-1], longest)
            H[-i-1] = longest

        return H
