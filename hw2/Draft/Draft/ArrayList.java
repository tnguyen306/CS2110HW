public class ArrayList<T> {
	private int counter;
	private T[] array;

	public ArrayList(int size) {
		counter = size;
	}

	public boolean isEmpty() {
		return counter == 0;
	}

	public boolean add(T elem) {
		if (elem == null) { throw new IllegalArgumentException(); }
		if (counter == array.length) { resize(); }
		array[counter] = elem;
		counter++;
		return true;
	}
}