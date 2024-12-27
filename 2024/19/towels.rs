use std::env;
use std::vec::Vec;
use std::fs::File;
use std::io::prelude::*;
use std::collections::HashSet;
use std::collections::HashMap;

fn split_lines(basic_line: &str) -> Vec<&str> {
    basic_line
        .trim()
        .split("\n")
        .collect()
}




fn can_create<'a>(remain: &'a str, towels: &HashSet<&str>, cache: &mut HashMap<&'a str, i64>) -> i64 {
    if remain.len() == 0 {
        return 1;
    }
    
    if cache.contains_key(remain) {
        // println!("Found {} it has {} ways", remain, *cache.get(&remain).unwrap());
        return *cache.get(&remain).unwrap();
    }
    let mut num_ways: i64 = 0;
    for j in 0..remain.len() {
        let slice = &remain[0..(j+1)];
        if towels.contains(slice) {
            num_ways += can_create(&remain[(j+1)..], &towels, cache );
        }
    }
    cache.insert(remain, num_ways);
    //println!("{} is possible in {} ways",remain, num_ways);
    return num_ways;


}

fn main() -> std::io::Result<()>{
    let args: Vec<_> = env::args().collect();
    //let mut to_plot: bool = false;
    if args.len() <= 1 {
        return Ok(());
    }
    /*if args.len() > 2 {
        to_plot = true;
    }*/
    let mut file = File::open(args[1].clone())?;
    let mut contents = String::new();
    file.read_to_string(&mut contents)?;
    let lines : Vec<&str> = split_lines(&contents);
    let mut towels: Vec<&str> = lines[0].split(", ").collect();
    towels.sort_by_key(|l| l.len());
    //println!("{:?}",towels);
    let towels_set: HashSet<&str> = towels.clone().into_iter().collect();
    //let new_towels_set = reduce_rules(&towels_set);
    //println!("{:?}", new_towels_set);
    let mut ans_a: usize = 0;
    let mut ans_b: i64 = 0;
    let mut cache: HashMap<&str, i64> = HashMap::new();
    for l in 2..lines.len() {
        // println!("{} - {}",l,lines[l]);
        let num_ways = can_create(lines[l], &towels_set, &mut cache);
        // println!("{}",num_ways);
        if num_ways != 0 {
            //println!("{} Okej!",lines[l]);
            ans_a += 1;
            ans_b += num_ways;
        } else {
            //println!("{} Inte okej!",lines[l]);
        }
    }
    println!("Anser part A: {}",ans_a);
    println!("Anser part B: {}",ans_b);
    Ok(())
}
