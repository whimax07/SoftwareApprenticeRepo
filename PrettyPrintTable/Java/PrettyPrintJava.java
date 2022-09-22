import java.util.ArrayList;

class PrettyPrintJava {

    public static void printTable(String[] headers, ArrayList<Object[]> data) {

    }

    public static void main(String[] args) {
        String[] headers = new String[]{"Name", "Language", "OS"};

        ArrayList<Object[]> data = new ArrayList<>();
        data.add(new Object[]{"a"});
        data.add(new Object[]{"b", "c"});

        printTable(new String[]{}, data);


    }

}

