# Quicksort algorithm implementation - https://www.javatpoint.com/quick-sort (Full explanation - https://en.wikipedia.org/wiki/Quicksort)


# @param array : an array of integers
# @param array_start_index : the index of the first element(usually 0)
# @param array_end_index : the index of the last element(usually "len(array)-1")
def partition(array, array_start_index, array_end_index):
	pivot = array[array_end_index] # the last(most right element) element would be used as the pivot
	current_left_side_element_index = array_start_index - 1 # pointer to the start of the array(most left element)

	for current_number_index in range(array_start_index, array_end_index): # go through all elements in the array
		if array[current_number_index] < pivot: # if the current number is smaller than the pivot
			current_left_side_element_index = current_left_side_element_index + 1 # move left side element index one step forward
			array[current_left_side_element_index], array[current_number_index] = array[current_number_index], array[current_left_side_element_index] # swap the current number with the number at current left side index. This is done so that all numbers smaller than the pivot(this is checked in the check above) are moved to the left side(and as the left side index is increased everytime before a number is moved to the left, they do not overwrite each other) and the left side numbers that were there before are moved onto the place of current number, it ends up that all smaller numbers are on the left side because all numbers smaller than the pivot are moved to the left side by swapping places(smaller number moves onto the place of a number in the left and number in the left moves onto the place where that number(which was smaller than the pivot) was) with the numbers that were there before. Numbers that are on the left before swapping are larger than the pivot because otherwise they would be swapped even closer to the left before and if they weren't and were just skipped then it is okay that they are moved onto the right side by being swapped with the numbers that were there before and are smaller than the pivot.

	array[current_left_side_element_index+1], array[array_end_index] = array[array_end_index], array[current_left_side_element_index+1] # after the loop which moves all numbers smaller than the pivot to the left is finished, swap the pivot with the number at the current left side element index, placing pivot into that location is correct as the last left side index is the element which has all numbers smaller than pivot on it's left and all elements larger on the right, so the pivot should be moved there after being in the end of the array during sorting to not interfere

	return current_left_side_element_index+1, array # return both the location where the pivot was moved(this is the location that splits the array into left side(numbers smaller than the pivot) and right side(numbers larger than the pivot)) and the changed array

# @param array : an array of integers
# @param array_start_index : the index of the first element(usually 0)
# @param array_end_index : the index of the last element(usually "len(array)-1")
def quicksort(array, array_start_index, array_end_index):
	if array_start_index < array_end_index: # error check the array start and end indices, because the array does not exist if the start index isn't smaller than end index
		# Here recursion is used to sort the array, firstly the partition() function is called to split the array into two parts using a pivot with numbers larger than the pivot on the right side and smaller on the left side, than it returns the changed array and the point where the array is split into two parts(larger and smaller), aftert the partition() function is called, quicksort recursively calls quicksort two times, first time to sort the smaller half and second time to sort the larger half of the array, and there quicksort functions called from quicksort call quicksort again which first splits the parts into more parts using parition() and than calls quicksort() again to split these parts into smaller parts and sort them... and it goes until the parts are 1 element in size(which means the arrays no longer pass the if check above) meaning the array is sorted and so eventually all quicksort functions return to each other and in the end everything is finally returned into the first quicksort() instance's array variable and it returns it to the caller
		partition_var, array = partition(array, array_start_index, array_end_index)
		array = quicksort(array, array_start_index, partition_var-1) # call quicksort, but pass the left side(with numbers smaller than the pivot) of the array partitioned by partition() function
		array = quicksort(array, partition_var + 1, array_end_index) # call quicksort, but pass the right side(with the numbers larger than the pivot) of the array paritioned by partition() function

	return array




array = [2, 3, 4, 14, 16, 3, 6, 11, 12, 20, 2, 7, 15, 16, 17, 8, 12, 13, 16, 20, 2, 6, 12, 14, 19, 7, 9, 10, 15, 17]
print(quicksort(array, 0, len(array)-1))