def lines(a, b):
    """Return lines in both a and b"""
    # Split strings into lines
    list_a = a.splitlines()
    list_b = b.splitlines()
    new_list = []

    new_list = list(set(list_a) & set(list_b))

    return new_list


def sentences(a, b):
    """Return sentences in both a and b"""
    from nltk.tokenize import sent_tokenize
    # Split strings into sentences
    list_a = sent_tokenize(a, language='english')
    list_b = sent_tokenize(b, language='english')
    new_list = []

    new_list = list(set(list_a) & set(list_b))

    return new_list


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    # Create empty lists
    list_a = []
    list_b = []
    new_list = []
    # Split each string into substrings of length n
    for i in range(len(a) - n + 1):
        list_a.append(a[i:i + n])

    for i in range(len(b) - n + 1):
        list_b.append(b[i:i + n])

    new_list = list(set(list_a) & set(list_b))

    return new_list