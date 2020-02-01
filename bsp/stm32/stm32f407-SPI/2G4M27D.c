/*
 * �����嵥������һ�� SPI �豸ʹ������
 * ���̵����� spi_w25q_sample ��������ն�
 * ������ø�ʽ��spi_w25q_sample spi10
 * ������ͣ�����ڶ���������Ҫʹ�õ�SPI�豸���ƣ�Ϊ����ʹ��Ĭ�ϵ�SPI�豸
 * �����ܣ�ͨ��SPI�豸��ȡ w25q �� ID ����
*/

#include <rtthread.h>
#include <rtdevice.h>

#define W25Q_SPI_DEVICE_NAME     "spi1"

static void spi_w25q_sample(int argc, char *argv[])
{
    struct rt_spi_device *spi_dev_w25q;
    char name[RT_NAME_MAX];
    rt_uint8_t w25x_read_id = 0x90;
    rt_uint8_t id[5] = {0};

    if (argc == 2)
    {
        rt_strncpy(name, argv[1], RT_NAME_MAX);
    }
    else
    {
        rt_strncpy(name, W25Q_SPI_DEVICE_NAME, RT_NAME_MAX);
    }

    /* ���� spi �豸��ȡ�豸��� */
    spi_dev_w25q = (struct rt_spi_device *)rt_device_find(name);
		rt_hw_spi_device_attach("spi1", "spi0", GPIOB,GPIO_PIN_0);
    if (!spi_dev_w25q)
    {
        rt_kprintf("spi sample run failed! can't find %s device!\n", name);
    }
		 else
    {
//        /* ��ʽ1��ʹ�� rt_spi_send_then_recv()���������ȡID */
     //  rt_spi_send_then_recv(spi_dev_w25q, &w25x_read_id, 1, id, 5);
		//	rt_kprintf("use rt_spi_send_then_recv() read w25q ID is:%x%x\n", id[3], id[4]);

//        /* ��ʽ2��ʹ�� rt_spi_transfer_message()���������ȡID */
        struct rt_spi_message msg1, msg2;

        msg1.send_buf   = &w25x_read_id;
        msg1.recv_buf   = RT_NULL;
        msg1.length     = 1;
        msg1.cs_take    = 1;
        msg1.cs_release = 0;
        msg1.next       = &msg2;

        msg2.send_buf   = RT_NULL;
        msg2.recv_buf   = id;
        msg2.length     = 5;
        msg2.cs_take    = 0;
        msg2.cs_release = 1;
        msg2.next       = RT_NULL;

        rt_spi_transfer_message(spi_dev_w25q, &msg1);
        rt_kprintf("use rt_spi_transfer_message() read w25q ID is:%x%x\n", id[3], id[4]);

    }
}
#if defined (RT_SAMPLES_AUTORUN) && defined(RT_USING_COMPONENTS_INIT)
    INIT_APP_EXPORT(spi_w25q_sample);
#endif