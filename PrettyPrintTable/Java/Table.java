import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public class Table {

    private final List<String> headers;

    private final int numHeaders;

    private final List<List<String>> data = new ArrayList<>();



    public Table(List<String> headers) {
        this.headers = headers;
        numHeaders = headers.size();
    }



    /**
     * This is the no expect version of the add a row to the table function.
     * @return false is the row has a different number of entries compared to headers.
     */
    public boolean addRow(List<String> row) {
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
    public boolean addRows(List<List<String>> rows) {
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

        private final List<Integer> headerWidths = new ArrayList<>();

        private static final int MARGIN = 1;

        // Add the symbols used as vars so changing them in one place propagates. You could use an enum for this as
        // well. Emitting this entirely is also a reasonable choice.
        private static final String HORIZONTAL = "-";
        private static final String VERTICAL = "|";
        private static final String CROSS = "+";



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


                // 3) Comparator provide a bunch of factory methods to make `Comparator`s.
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
            headerWidths.forEach(width -> {
                builder.append(CROSS);
                builder.append(HORIZONTAL.repeat(width + MARGIN * 2));
            });
            builder.append(CROSS);
            builder.append("\n");
        }

        private void addRow(List<String> row) {
            // NOTE(Max): Needing to use a normal for-loop here is a weakness of Java streams. Which is a shame as this
            // is where you really want them in case of a length mismatch. Something like the link would be preferred in
            // a real code base. https://stackoverflow.com/a/34804751
            for (int i = 0; i < numHeaders; i++) {
                String item = row.get(i);
                int width = headerWidths.get(i);
                int spaceNeedsToBeFilled = width - item.length();

                builder.append(VERTICAL);
                builder.append(" ".repeat(MARGIN));
                builder.append(item);
                builder.append(" ".repeat(spaceNeedsToBeFilled + MARGIN));
            }
            builder.append(VERTICAL);
            builder.append("\n");
        }

        private void addHeaders() {
            addRow(headers);
        }

        private void addData() {
            data.forEach(this::addRow);
        }

    }

}
