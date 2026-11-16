// SPDX-License-Identifier: Dual BSD/GPL
/*
 * Copyright (c) 2017, GlobalLogic Ukraine LLC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by the GlobalLogic.
 * 4. Neither the name of the GlobalLogic nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY GLOBALLOGIC UKRAINE LLC ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL GLOBALLOGIC UKRAINE LLC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include "hello1.h"

MODULE_AUTHOR("Denys Orieshyn <orieshyn.denys_io46@edu.kpi.ua>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training: print_hello() user");
MODULE_LICENSE("Dual BSD/GPL");

static unsigned int howmany = 1;
module_param(howmany, uint, 0444);
MODULE_PARM_DESC(howmany, "Number of greetings to print (default 1; 0 and 5..10 warn; >10 rejected)");

static int __init hello2_init(void)
{
	unsigned int i;
	int err;

	if (howmany == 0 || (howmany >= 5 && howmany <= 10))
		pr_warn("Warning: howmany is %u (0 or between 5 and 10)\n",
			howmany);

	if (howmany > 10) {
		pr_err("Error: howmany is %u (> 10). Module not loaded!\n",
		       howmany);
		return -EINVAL;
	}

	for (i = 0; i < howmany; i++) {
		err = print_hello();
		if (err) {
			pr_err("Error: print_hello() failed (%d)\n", err);
			return err;
		}
	}

	return 0;
}

static void __exit hello2_exit(void)
{
	/* Do nothing here right now */
}

module_init(hello2_init);
module_exit(hello2_exit);
