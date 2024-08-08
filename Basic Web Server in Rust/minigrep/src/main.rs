#[warn(unused_imports)]
use std::env;
use std::process;

use minigrep::Config;

fn main() {
    let config = Config::new(env::args()).unwrap_or_else(|err| {
        eprintln!("Problem Parsing Arguments : {err}");
        process::exit(1);
    });

    println!("Searching for {}", config.query);
    println!("In File {}", config.file_path);

    if let Err(e) = minigrep::run(config) {
        eprintln!("Application Error: {e}");
        process::exit(1);
    }
}



  
