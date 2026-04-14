fn create_data() -> Vec<i32> {
    vec![10, 20, 30, 40, 50]
}

fn sum_data(data: &[i32]) -> i32 {
    data.iter().sum()
}

fn transform_data(mut data: Vec<i32>) -> Vec<i32> {
    for val in data.iter_mut() {
        *val *= 2;
    }
    data
}

fn main() {
    let data = create_data();
    println!("created: {:?}", data);
    let total = sum_data(&data);
    println!("sum: {}", total);
    let data = transform_data(data);
    println!("transformed: {:?}", data);
    println!("freed");
}
