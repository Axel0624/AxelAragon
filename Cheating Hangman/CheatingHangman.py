from random import choice

def load_words(filename, length):
    try:
        with open(filename) as f:
            return [i.strip().lower() for i in f if len(i.strip()) == length]
    except FileNotFoundError:
        print("File not found")
        return []

def game_over(guesses_remaining, hint):
    if guesses_remaining <= 0:
        return True
    if hint.count("-") == 0:
        return True
    return False

def mask_word(word, guessed):
    """Returns word with all letters not in guessed replaced with hyphens
    Args:
        word (str): the word to mask
        guessed (set): the guessed letters
    Returns:
        str: the masked word
    """ 
    result = ""
    for character in word:
        if character in guessed:
            result += character
        else:
            result += "-"
    return result

def partition(words, guessed):
    """Generates the partitions of the set words based upon guessed

    Args:
        words (set): the word set
        guessed (set): the guessed letters

    Returns:
        dict: The partitions
    """
    partitions = {}

    for word in words:
        masked_word = mask_word(word, guessed)
        if masked_word not in partitions:
            partitions[masked_word] = [word]
        else:
            partitions[masked_word].append(word)
    return partitions

def max_partition(partitions):
    """Returns the hint for the largest partite set

    The maximum partite set is selected by selecting the partite set with
    1. The maximum size partite set
    2. If more than one maximum, prefer the hint with fewer revealed letters
    3. If there is still a tie, select randomly

    Args:
        partitions (dict): partitions from partition function

    Returns:
        str: hint for the largest partite set
    """
    max_size = 0
    max_hint = None

    for hint, words in partitions.items():
        size = len(words)
        if size > max_size:
            max_size = size
            max_hint = hint
        elif size == max_size and max_hint and hint.count("-") < max_hint.count("-"):
            max_hint = hint

    return max_hint

def read_input(guesses):
    while True:
        guess = input("Enter a letter: ").lower()
        if len(guess) != 1:
            print("Enter only one letter")
        elif not guess.isalpha():
            print("That isn't a letter, try again")
        elif guess in guesses:
            print("You already guessed that, try again")
        else:
            return guess

def read_int():
    while True:
        try:
            length = int(input("What word length? "))
            return length
        except ValueError:
            print("That isn't a number, try again")

def main():
    length = read_int()
    cheat = length < 0
    length = abs(length)
    words = load_words("hangman_words.txt", length)
    if len(words) < 1:
        print("No words found of that length")
        return
    answer = choice(words)
    guesses_remaining = 5
    guesses = set()
    hint = mask_word(answer, guesses)

    if cheat:
        print(f"Selected partition: {max_partition(partition(words, guesses))}")

    while not game_over(guesses_remaining, hint):
        print(f"You have {guesses_remaining} incorrect guesses remaining")
        print(f"Hint: {hint}")
        print(f"Guessed letters: {guesses}")
        
        guess = read_input(guesses)
        guesses.add(guess)
        next_hint = mask_word(answer, guesses)
        if hint != next_hint:
            print(f"Correct! '{guess}' is in the word!")
        else:
            print(f"I'm sorry, '{guess}' is not in the word")
            guesses_remaining -= 1
        hint = next_hint

    if hint.count("-") == 0:
        print(f"You win! The word was '{answer}'")
    else:
        print(f"You lose! The word was '{answer}'")

if __name__ == "__main__":
    main()
