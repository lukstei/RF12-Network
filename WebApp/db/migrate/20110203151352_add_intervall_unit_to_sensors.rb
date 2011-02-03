class AddIntervallUnitToSensors < ActiveRecord::Migration
  def self.up
	add_column :sensors, :intervall_unit, :string 
  end

  def self.down
	remove_column :sensors, :intervall_unit
  end
end
