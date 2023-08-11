provider "aws" {
  region = "us-east-1"  # Replace with your desired region
}

resource "aws_instance" "vm" {
  count = 100  # Create 100 instances

  ami           = "ami-0c55b159cbfafe1f0"  # Replace with your desired AMI ID
  instance_type = "t2.micro"
  
  tags = {
    Name = "VM-${count.index}"
  }

  # Intentional mistake: Missing "subnet_id" attribute
  vpc_security_group_ids = ["sg-0123456789abcdef0"]
}
