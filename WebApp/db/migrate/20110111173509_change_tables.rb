class ChangeTables < ActiveRecord::Migration
  def self.up
	drop_table :groups_sensors
	remove_column :measured_datas, :messdaten_float
  end

  def self.down
	create_table "groups_sensors", :id => false do |t|
		t.integer :group_id
		t.integer :sensor_id
	end 
	add_column :measured_datas, :messdaten_float, :float
  end
end
