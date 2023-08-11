provider "aws" {
  region = "us-west-2"
}

resource "aws_instance" "example" {
  ami           = "ami-12345678"
  instance_type = "t2.micro"

  # Deliberate mistake: Missing "tags" block
}

resource "aws_s3_bucket" "my_bucket" {
  bucket = "my-unique-bucket"
  acl    = "public-read"
  
  # Deliberate mistake: Missing "tags" block
}
