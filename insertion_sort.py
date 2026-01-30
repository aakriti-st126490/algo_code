def insertion_sort(arr):
    """
    Sorts an array using the insertion sort algorithm.

    Parameters:
    arr (list): A list of elements to be sorted.

    Returns:
    list: A new list containing the sorted elements.
    """
    # Create a copy of the array to avoid modifying the original
    sorted_arr = arr.copy()
    
    # Traverse through 1 to len(sorted_arr)
    for i in range(1, len(sorted_arr)):
        key = sorted_arr[i]
        j = i - 1
        
        # Move elements of sorted_arr[0..i-1], that are greater than key,
        # to one position ahead of their current position
        while j >= 0 and key < sorted_arr[j]:
            sorted_arr[j + 1] = sorted_arr[j]
            j -= 1
        sorted_arr[j + 1] = key
    
    return sorted_arr

# Example usage:
if __name__ == "__main__":
    sample_array = [12, 11, 13, 5, 6]
    print("Original array:", sample_array)
    sorted_array = insertion_sort(sample_array)
    print("Sorted array:", sorted_array)