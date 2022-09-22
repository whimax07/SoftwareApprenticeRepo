import java.util.ArrayList;
import java.util.Comparator;

public class Table {

    private final ArrayList<String> headers;

    private final int numHeaders;

    private final ArrayList<ArrayList<String>> data = new ArrayList<>();



    public Table(ArrayList<String> headers) {
        this.headers = headers;
        numHeaders = headers.size();
    }



    /**
     * This is the no expect version of the add a row to the table function.
     * @return false is the row has a different number of entries compared to headers.
     */
    public boolean addRow(ArrayList<String> row) {
        if (row.size() == numHeaders) {
            data.add(row);
            return true;
        }

        return false;
    }

    /**
     * This is the no expect version of the add some number of rows to the table function.
     * @return false if any of the rows has a different number of entries compared to headers.
     */
    public boolean addRows(ArrayList<ArrayList<String>> rows) {
        if (rows.size() == 0) {
            return true;
        }

        for (var row : rows) {
            if (row.size() != numHeaders) {
                return false;
            }
        }

        data.addAll(rows);
        return true;
    }



    @Override
    public String toString() {
        return new StringifyTable().builder.toString();
    }


    private class StringifyTable {

        public StringBuilder builder = new StringBuilder();

        private final ArrayList<Integer> headerWidths = new ArrayList<>();



        public StringifyTable() {
            findColumnWidths();

            addLine();
            addHeaders();
            addLine();
            addData();
            addLine();
        }



        private void findColumnWidths() {
            for (int i = 0; i < numHeaders; i++) {
                // NOTE(Max): There are a couple of different ways to write the find bit that finds the width of a
                // column, I've done a couple of them. The 3rd one is more of an example of how streams work.

                // 1) The normal way.
                int width_a = headers.get(i).length();
                for (var row : data) {
                    width_a = Math.max(width_a, row.get(i).length());
                }
                headerWidths.add(width_a);


                final int finalI = i;

                // 2) This one I quite like.
                var width_b = data.stream().mapToInt(row -> row.get(finalI).length()).max().orElse(0);
                width_b = Math.max(width_b, headers.get(i).length());
                // NOTE(Max): Because I am repeating work instead of having these as comments we need to use the set
                // method instead of the add method below.
                headerWidths.set(i, width_b);


                // 3) This works and is cool, but I can't recommend it.
                var width_c = data.stream().max(
                        Comparator.comparingInt(row -> row.get(finalI).length())
                ).orElse(headers).get(i).length();
                width_c = Math.max(width_c, headers.get(i).length());
                // NOTE(Max): Because I am repeating work instead of having these as comments we need to use the set
                // method instead of the add method below.
                headerWidths.set(i, width_c);
            }
        }

        private void addLine() {

        }

        private void addHeaders() {

        }

        private void addData() {

        }

    }

}
