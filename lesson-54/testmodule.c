/**
 *  25.12.2023
 *
 *  Модуль ядра, демонстрирующий обмен с user-space с помощью файла символьного
 *  устройства.
*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/rwlock.h>
#define DEV_NAME "testmodule"

static int major = 0;
static rwlock_t lock;
static char test_string[15] = "Hello!\0";

ssize_t test_read(struct file *fd, char *buf, size_t size, loff_t *off)
{
    size_t rc;
    read_lock(&lock);
    rc = simple_read_from_buffer(buf, size, off, test_string, 15);
    read_unlock(&lock);
    return rc;
}

ssize_t test_write(struct file *fd, const char *buf, size_t size, loff_t *off)
{
    size_t rc = 0;
    if (size > 15)
    {
        return -EINVAL;
    }

    write_lock(&lock);
    rc = simple_write_to_buffer(test_string, 15, off, buf, size);
    write_unlock(&lock);
    return rc;
}

/* Переопределение функций записи и чтения */
static const struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = test_read,
    .write = test_write
};


/* Вызывается при загрузке */
int init_module(void)
{
    pr_info("testmodule loaded!\n");   /* Запись в лог */
    rwlock_init(&lock);

    /* Регистрация символьного устройства */
    major = register_chrdev(major, DEV_NAME, &fops);
    if (major < 0)
    {
        return major;
    }

    pr_info("Major: %d\n", major);
    return 0;
}

/* Вызывается при выгрузке */
void cleanup_module(void)
{
    unregister_chrdev(major, DEV_NAME);
    pr_info("testmodule unloaded!\n");
}

/* Использование лицензии для доступа к функционалу ядра */
MODULE_LICENSE("GPL");
