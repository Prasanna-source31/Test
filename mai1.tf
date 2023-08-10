resource "aws_security_group" "sg_ping" {
   name = "Allow Ping"

-  ingress {
-    from_port       = -1
-    to_port         = -1
-    protocol        = "icmp"
-    security_groups = [aws_security_group.sg_8080.id]
-  }
 }

 resource "aws_security_group" "sg_8080" {
  name = "Allow 8080"
  egress {
    // ...
    cidr_blocks = "invalid_cidr"  // Incorrect format
  }
}
   }
 }