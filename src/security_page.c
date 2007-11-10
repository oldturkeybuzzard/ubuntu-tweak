#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "ubuntu-tweak.h"

static gchar *lockdown_keys[6]={
	"/desktop/gnome/lockdown/disable_command_line",
	"/desktop/gnome/lockdown/disable_lock_screen",
	"/desktop/gnome/lockdown/disable_printing",
	"/desktop/gnome/lockdown/disable_print_setup",
	"/desktop/gnome/lockdown/disable_save_to_disk",
	"/desktop/gnome/lockdown/disable_user_switching",
};

static gchar *disable_dir="/desktop/gnome/lockdown";

/*expert mode*/
static GtkWidget *expander_security;
static GtkWidget *expert_label_security;
static GtkWidget *expert_box_security;
static GtkWidget *expert_runapplication;
static GtkWidget *expert_lockscreen;
static GtkWidget *expert_printing;
static GtkWidget *expert_printsetup;
static GtkWidget *expert_savetodisk;
static GtkWidget *expert_userswitching;
static gpointer present_expert_security;

static void show_expert_label_security()
{
	if(present_expert_security!=NULL){
		gtk_widget_hide(present_expert_security);
	}
	expert_label_security=nt_expert_content_new_with_string(_("Within this menu are advanced security settings. If you require more information about a specific option, move your cursor over that option, and a description will appear here."));
	gtk_widget_show(expert_label_security);
	present_expert_security=expert_label_security;
	gtk_box_pack_start(GTK_BOX(expert_box_security),expert_label_security,TRUE,TRUE,0);
}

static void expander_change_security(GtkWidget *widget,gpointer data)
{
	gboolean bool;
	bool=gtk_expander_get_expanded(GTK_EXPANDER(widget));	
	if(bool==FALSE){
		show_expert_label_security();
	}
}

static void show_expert_runapplication(GtkWidget *widget,gpointer data)
{
	if(present_expert_security!=expert_runapplication){
		gtk_widget_hide(present_expert_security);
		expert_runapplication=nt_expert_content_new_with_string(_("This option enables and disables the Run Application dialog.\nThe default key combination for Run is \"Alt+F2\".\nThis is one way of preventing users from running commands you don't want them to."));
		gtk_widget_show(expert_runapplication);
		present_expert_security=expert_runapplication;
		gtk_box_pack_start(GTK_BOX(expert_box_security),expert_runapplication,FALSE,FALSE,0);
	}
}

static void show_expert_lockscreen(GtkWidget *widget,gpointer data)
{
	if(present_expert_security!=expert_lockscreen){
		gtk_widget_hide(present_expert_security);
		expert_lockscreen=nt_expert_content_new_with_string(_("This option enables and disables locking of the screen.\nYou are required to enter your password when unlocking a locked screen.\nThis could be useful on a public terminal, such as at a school or web cafe."));
		gtk_widget_show(expert_lockscreen);
		present_expert_security=expert_lockscreen;
		gtk_box_pack_start(GTK_BOX(expert_box_security),expert_lockscreen,FALSE,FALSE,0);
	}
}

static void show_expert_printing(GtkWidget *widget,gpointer data)
{
	if(present_expert_security!=expert_printing){
		gtk_widget_hide(present_expert_security);
		expert_printing=nt_expert_content_new_with_string(_("This option enables and disables Printing in all applications."));
		gtk_widget_show(expert_printing);
		present_expert_security=expert_printing;
		gtk_box_pack_start(GTK_BOX(expert_box_security),expert_printing,FALSE,FALSE,0);
	}
}

static void show_expert_printsetup(GtkWidget *widget,gpointer data)
{
	if(present_expert_security!=expert_printsetup){
		gtk_widget_hide(present_expert_security);
		expert_printsetup=nt_expert_content_new_with_string(_("This option enables and disables Print Setup in all applications.\nThis could be useful to restrict printing options such as installed printers, drivers, and printer sharing."));
		gtk_widget_show(expert_printsetup);
		present_expert_security=expert_printsetup;
		gtk_box_pack_start(GTK_BOX(expert_box_security),expert_printsetup,FALSE,FALSE,0);
	}
}

static void show_expert_savetodisk(GtkWidget *widget,gpointer data)
{
	if(present_expert_security!=expert_savetodisk){
		gtk_widget_hide(present_expert_security);
		expert_savetodisk=nt_expert_content_new_with_string(_("This option enables and disables the \"Save\" and \"Save As\" function in all applications.\nThis option could be used to restrict file write access on a system."));
		gtk_widget_show(expert_savetodisk);
		present_expert_security=expert_savetodisk;
		gtk_box_pack_start(GTK_BOX(expert_box_security),expert_savetodisk,FALSE,FALSE,0);
	}
}
static void show_expert_userswitching(GtkWidget *widget,gpointer data)
{
	if(present_expert_security!=expert_userswitching){
		gtk_widget_hide(present_expert_security);
		expert_userswitching=nt_expert_content_new_with_string(_("This option enables and disables User Switching.\nThis could be useful on a public terminal, such as at a school or web cafe, or to provide security to other logged-in users."));
		gtk_widget_show(expert_userswitching);
		present_expert_security=expert_userswitching;
		gtk_box_pack_start(GTK_BOX(expert_box_security),expert_userswitching,FALSE,FALSE,0);
	}
}

GtkWidget *create_disable_page()
{
	GtkWidget *main_vbox;
	GtkWidget *vbox;
	GtkWidget *hbox;
	GtkWidget *label;
	GtkWidget *checkbutton;

	main_vbox=gtk_vbox_new(FALSE,10);
	gtk_widget_show(main_vbox);
	gtk_container_set_border_width(GTK_CONTAINER(main_vbox),5);

	label=gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label),_("<b>System Security options</b>"));
	gtk_misc_set_alignment(GTK_MISC(label),0,0);
	gtk_widget_show(label);
	gtk_box_pack_start(GTK_BOX(main_vbox),label,FALSE,FALSE,0);
	
	hbox=gtk_hbox_new(FALSE,10);
	gtk_widget_show(hbox);
	gtk_box_pack_start(GTK_BOX(main_vbox),hbox,FALSE,FALSE,0);
	
	label=gtk_label_new(" ");
	gtk_widget_show(label);
	gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,0);

	vbox=gtk_vbox_new(FALSE,0);
	gtk_widget_show(vbox);
	gtk_box_pack_start(GTK_BOX(hbox),vbox,FALSE,FALSE,0);

	checkbutton=ut_checkbutton_new_with_gconf(_("Disable \"Run Application\" dialog (Alt+F2)"),lockdown_keys[0],disable_dir,ut_checkbutton_toggled,show_expert_runapplication);
	gtk_widget_show(checkbutton);
	gtk_box_pack_start(GTK_BOX(vbox),checkbutton,FALSE,FALSE,0);

	checkbutton=ut_checkbutton_new_with_gconf(_("Disable Lock Screen (Ctrl+Alt+L)"),lockdown_keys[1],disable_dir,ut_checkbutton_toggled,show_expert_lockscreen);
	gtk_box_pack_start(GTK_BOX(vbox),checkbutton,FALSE,FALSE,0);

	checkbutton=ut_checkbutton_new_with_gconf(_("Disable Printing"),lockdown_keys[2],disable_dir,ut_checkbutton_toggled,show_expert_printing);
	gtk_box_pack_start(GTK_BOX(vbox),checkbutton,FALSE,FALSE,0);

	checkbutton=ut_checkbutton_new_with_gconf(_("Disable Print Setup"),lockdown_keys[3],disable_dir,ut_checkbutton_toggled,show_expert_printsetup);
	gtk_box_pack_start(GTK_BOX(vbox),checkbutton,FALSE,FALSE,0);

	checkbutton=ut_checkbutton_new_with_gconf(_("Disable Save To Disk"),lockdown_keys[4],disable_dir,ut_checkbutton_toggled,show_expert_savetodisk);
	gtk_box_pack_start(GTK_BOX(vbox),checkbutton,FALSE,FALSE,0);

	checkbutton=ut_checkbutton_new_with_gconf(_("Disable User Switching"),lockdown_keys[5],disable_dir,ut_checkbutton_toggled,show_expert_userswitching);
	gtk_box_pack_start(GTK_BOX(vbox),checkbutton,FALSE,FALSE,0);

/*expander*/
	expander_security=gtk_expander_new_with_mnemonic(_("Need some help? Click here!"));
	gtk_widget_show(expander_security);
	g_signal_connect(G_OBJECT(expander_security),"activate",G_CALLBACK(expander_change_security),NULL);
	gtk_box_pack_end(GTK_BOX(main_vbox),expander_security,FALSE,FALSE,0);

	expert_box_security=gtk_vbox_new(FALSE,0);
	gtk_widget_set_size_request(GTK_WIDGET(expert_box_security),200,100);
	gtk_widget_show(expert_box_security);
	gtk_container_add(GTK_CONTAINER(expander_security),expert_box_security);

	return main_vbox; 
}