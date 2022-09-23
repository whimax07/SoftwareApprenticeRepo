import java.util.Arrays;

class PrettyPrintJava {

    public static void main(String[] args) {
        Table table = new Table(Arrays.asList("Name", "Language", "OS"));
        table.addRows(
                Arrays.asList(
                        Arrays.asList("Max", "Java", "Windows"),
                        Arrays.asList("Adam", "C++", "Linux"),
                        Arrays.asList("James", "Python", "Windows"),
                        Arrays.asList("Josh", "Python", "Linux")
                )
        );

        System.out.println(table);
    }

}
